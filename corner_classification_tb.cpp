#include "xf_headers.h"
#include "xf_threshold_config.h"
#include "xf_erosion_config.h"
#include "xf_dilation_config.h"
#include "xf_harris_config.h"
#include "corner_classification.h"
#include "corner_classification_test_code.h"
#include "tb_utils.h"



int main(int argc, char** argv)
{


	static xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> img1, img2;

	load_image("intermediate_steps/step_5.jpg",img1);
//	step_executer(img1, img2, 5, 5);
//	xf::imwrite("step_5.jpg",img2);

	//-----------------------------------------------------------------------------------------------------------------
	ROI RoI;

	//test code
	cv::Mat image_to_draw;
	image_to_draw = cv::imread("Borders/border_4_resized_2.jpg", CV_LOAD_IMAGE_COLOR);
	RoI = corner_classification_testing(img1, image_to_draw);
//	std::cout << "<------------------------------------------------>\n";
//	ROI RoI2 = corner_classification_testing_2(img5, image_to_draw);
//
//
//
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
//
//
	std::cout << "ROI:\n";
	std::cout << "R1 " << RoI.x1 << "  " << RoI.y1;
	std::cout << "\nR2 " << RoI.x2 << "  " << RoI.y2;
	std::cout << "\nR3 " << RoI.x3 << "  " << RoI.y3;
	std::cout << "\nR4 " << RoI.x4 << "  " << RoI.y4;

	std::cout << "\n\n";
//
//	std::cout << "ROI 2:\n";
//	std::cout << "R1 " << RoI2.x1 << "  " << RoI2.y1;
//	std::cout << "\nR2 " << RoI2.x2 << "  " << RoI2.y2;
//	std::cout << "\nR3 " << RoI2.x3 << "  " << RoI2.y3;
//	std::cout << "\nR4 " << RoI2.x4 << "  " << RoI2.y4;
//
//	std::cout << "\n\n";
//

	return 0;
}
