#include "xf_headers.h"
//#include "xf_threshold_config.h"
//#include "xf_erosion_config.h"
//#include "xf_dilation_config.h"
//#include "xf_harris_config.h"
//#include "corner_classification.h"
//#include "corner_classification_test_code.h"
#include "pixel_remapper.h"
#include "tb_utils.h"


int main(int argc, char** argv)
{

	pixel_remap_test();
	/*
	cv::Mat in_img;
	in_img = cv::imread("cemva_images/blobs_1_step_5.jpg",0);

	for (int i = 0; i < in_img.rows - 2; i++){
				for (int j = 0; j < in_img.cols - 2; j++){
						//print the location of the corner
					if (in_img.at<float>(i,j) != 0){
						point p = pixel_remap(i, j);
						std::cout << "(" << j << ", " << i << ") --> " << p.x << " " << p.y << std::endl;
					}

				}
			}

 */
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
