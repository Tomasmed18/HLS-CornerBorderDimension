#include "xf_headers.h"
#include "corner_classification_test_code.h"
#include "xf_ip_accel_app_config.h"
#include "pixel_remapper.h"
#include "tb_utils.h"

#define T unsigned char

void test_y(int x, int y, int result){
	std::cout << "x " << x << " y " << y << " --->  " << result << ":" << pixel_remap(x, y).y << "\n\n";
}

int main(int argc, char** argv)
{

	if(argc != 2)
		{
			fprintf(stderr,"Invalid Number of Arguments!\nUsage:\n");
			fprintf(stderr,"<Executable Name> <input image path> \n");
			return -1;
		}

		cv::Mat in_img;
		cv::Mat out_img;

		// reading in the color image
		in_img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
		if (in_img.data == NULL)
		{
			fprintf(stderr,"Cannot open image at %s\n", argv[1]);
			return 0;
		}
		out_img.create(HEIGHT, WIDTH,CV_8UC1);

		uint16_t height = in_img.rows;
		uint16_t width = in_img.cols;


		hls::stream< ap_axiu<8,1,1,1> > _src,_dst;

		#if __SDSCC__
		perf_counter hw_ctr;
		hw_ctr.start();
		#endif

		cvMat2AXIvideoxf<NPC1>(in_img, _src);

		ip_accel_app(_src, _dst);

		AXIvideo2cvMatxf<NPC1>(_dst, out_img);

		#if __SDSCC__
		hw_ctr.stop();
		uint64_t hw_cycles = hw_ctr.avg_cpu_cycles();
		#endif

		cv::imwrite("hls_out.png", out_img);


//	cv::Mat in_img = cv::imread("cemva_images/blobs_1_step_5.jpg",0);
//
//	for (int i = 0; i < in_img.rows; i++){
//		for (int j = 0; j < in_img.cols; j++){
//			T val = in_img.at<T>(i,j);
//			if (val > 200){
//				point p = pixel_remap(i, j);
//				std::cout << "(" << j << ", " << i << ") --> " << p.x << " " << p.y << std::endl;
//			}
//
//		}
//	}
//
//	std::cout << "************************************************************************************";


//	cv::Mat image_to_draw = cv::imread("cemva_images/remapped_2.png",CV_LOAD_IMAGE_COLOR);
//	static xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> img1;
//	ROI RoI;
//	load_image("cemva_images/blobs_1_step_5_2.jpg",img1);
//
//
//
//	RoI = corner_classification_testing(img1, image_to_draw);



//	if (result == NO_ERROR)
//		std::cout << "--> No error\n\n";
//	if (result == CORNER_ERROR)
//			std::cout << "--> Corner error\n\n";
//	if (result == BORDER_ERROR)
//			std::cout << "--> Border error\n\n";
//	if (result == DIMENSION_ERROR)
//			std::cout << "--> Dimension error\n\n";


//	test_y( 756 , 628 , 728 );
//	test_y( 438 , 289 , 448 );
//	test_y( 1059 , 1603 , 1019 );
//	test_y( 614 , 805 , 604 );
//	test_y( 513 , 628 , 518 );
//	test_y( 256 , 1220, 296 );
//	test_y( 739 , 875, 711 );
//	test_y( 45 , 9, 71 );
//	test_y( 668 , 1580 , 657 );
//	test_y( 677 , 1797, 669 );
//	test_y( 850 , 1911, 835 );
//	test_y( 25 , 1136, 91 );
//	test_y( 524 , 107 , 526 );
//	test_y( 1066 , 568, 1010 );
//	test_y( 861 , 1247, 820 );
//	test_y( 16 , 972, 83 );
//	test_y( 135 , 1455, 180 );
//	test_y( 305 , 950, 341 );
//	test_y( 649 , 1691 , 642 );
//	test_y( 618 , 692, 609 );

	//pixel_remap_test();

/*
	cv::Mat in_img = cv::imread("cemva_images/blobs_1_step_5.jpg",0);
	cv::Mat remapped(1080, 1920, CV_8UC1);

	for (int i = 0; i < in_img.rows; i++){
				for (int j = 0; j < in_img.cols; j++){
					T val = in_img.at<T>(i,j);
					if (val > 200){
						point p = pixel_remap(i, j);
						std::cout << "(" << j << ", " << i << ") --> " << p.x << " " << p.y << std::endl;
						if ((p.x < remapped.cols) && (p.y < remapped.rows))
							remapped.at<T>(p.y,p.x) = 255;
					}

				}
			}
	cv::imwrite("remapped.png", remapped);
 /**/
	/*
	static xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> img1, img2, img3, img4, img5;

	load_image("cemva_images/blobs_1.png",img1);

	std::cout << ".... Step 2 ....\n\n";
	step_executer(img1, img2, 2, 2);
	xf::imwrite("blobs_1_step_2.jpg",img2);

	std::cout << ".... Step 3 ....\n\n";
	step_executer(img2, img3, 3, 3);
	xf::imwrite("blobs_1_step_3.jpg",img3);

	std::cout << ".... Step 4 ....\n\n";
	step_executer(img3, img4, 4, 4);
	xf::imwrite("blobs_1_step_4.jpg",img4);

	std::cout << ".... Step 5 ....\n\n";
	step_executer(img1, img5, 5, 5);
	xf::imwrite("blobs_1_step_5.jpg",img5);

	/**/

	//-----------------------------------------------------------------------------------------------------------------
/*
	ROI RoI;

	//test code
	cv::Mat image_to_draw;
	image_to_draw = cv::imread("Borders/border_4_resized_2.jpg", CV_LOAD_IMAGE_COLOR);
	RoI = corner_classification_testing(img1, image_to_draw);
	std::cout << "<------------------------------------------------>\n";
	ROI RoI2 = corner_classification_testing_2(img2, image_to_draw);



	int result = corner_classification(img2, RoI);

	if (result == NO_ERROR)
		std::cout << "--> No error\n\n";
	if (result == CORNER_ERROR)
			std::cout << "--> Corner error\n\n";
	if (result == BORDER_ERROR)
			std::cout << "--> Border error\n\n";
	if (result == DIMENSION_ERROR)
			std::cout << "--> Dimension error\n\n";


	std::cout << "ROI:\n";
	std::cout << "R1 " << RoI.x1 << "  " << RoI.y1;
	std::cout << "\nR2 " << RoI.x2 << "  " << RoI.y2;
	std::cout << "\nR3 " << RoI.x3 << "  " << RoI.y3;
	std::cout << "\nR4 " << RoI.x4 << "  " << RoI.y4;

	std::cout << "\n\n";

	std::cout << "ROI 2:\n";
	std::cout << "R1 " << RoI2.x1 << "  " << RoI2.y1;
	std::cout << "\nR2 " << RoI2.x2 << "  " << RoI2.y2;
	std::cout << "\nR3 " << RoI2.x3 << "  " << RoI2.y3;
	std::cout << "\nR4 " << RoI2.x4 << "  " << RoI2.y4;

	std::cout << "\n\n";
	*/

	std::cout << "***** FINISH *****\n\n";
	return 0;
}
