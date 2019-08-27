#include "xf_headers.h"
#include "xf_threshold_config.h"
#include "xf_erosion_config.h"
#include "xf_dilation_config.h"
#include "xf_harris_config.h"
#include "corner_classification.h"
#include "corner_classification_test_code.h"

void step_2(xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _src, xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _out){
	threshold_accel(_src, _out);
}

void step_3(xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _src, xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _out){

	cv::Mat element = cv::getStructuringElement( KERNEL_SHAPE,cv::Size(FILTER_SIZE, FILTER_SIZE), cv::Point(-1, -1));
	unsigned char structure_element[FILTER_SIZE*FILTER_SIZE];
	for(int i=0;i<(FILTER_SIZE*FILTER_SIZE);i++)
	{
		structure_element[i]=element.data[i];
	}

	erosion_accel(_src, _out, structure_element);
}

void step_4(xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _src, xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _out){

	cv::Mat element = cv::getStructuringElement( KERNEL_SHAPE,cv::Size(FILTER_SIZE, FILTER_SIZE), cv::Point(-1, -1));
	unsigned char structure_element[FILTER_SIZE*FILTER_SIZE];
	for(int i=0;i<(FILTER_SIZE*FILTER_SIZE);i++)
	{
		structure_element[i]=element.data[i];
	}

	dilation_accel(_src, _out, structure_element);
}

void step_5(xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _src, xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _out){
	harris_accel(_src, _out);
}

int main(int argc, char** argv)
{

	cv::Mat in_img;


	/*  reading in the color image  */
	in_img = cv::imread("Borders/border_4_resized_2.jpg",0);

	if (in_img.data == NULL)
	{
		fprintf(stderr,"Cannot open image at %s\n",argv[1]);
		return 0;
	}


	static xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> img1;
	static xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> img2;
	static xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> img3;
	static xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> img4;
	static xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> img5;

	//STEP 1
	img1.copyTo(in_img.data);
	xf::imwrite("step_1.png",img1);

	//STEP 2
	step_2(img1, img2);
	xf::imwrite("step_2.png",img2);


	//STEP 3
	step_3(img2, img3);
	xf::imwrite("step_3.png",img3);


	//STEP 4
	step_4(img3, img4);
	xf::imwrite("step_4.png",img4);


	//STEP 5
	step_5(img4, img5);
	xf::imwrite("step_5.png",img5);


	//-----------------------------------------------------------------------------------------------------------------
	ROI RoI;

	//test code
	cv::Mat image_to_draw;
	image_to_draw = cv::imread("Borders/border_4_resized_2.jpg", CV_LOAD_IMAGE_COLOR);
	RoI = corner_classification_testing(img5, image_to_draw);
	std::cout << "<------------------------------------------------>\n";
	ROI RoI2 = corner_classification_testing_2(img5, image_to_draw);



//	int result = corner_classification(img5, RoI);
//
//	if (result == NO_ERROR)
//		std::cout << "--> No error\n\n";
//	if (result == CORNER_ERROR)
//			std::cout << "--> Corner error\n\n";
//	if (result == BORDER_ERROR)
//			std::cout << "--> Border error\n\n";
//	if (result == DIMENSION_ERROR)
//			std::cout << "--> Dimension error\n\n";


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





	return 0;
}
