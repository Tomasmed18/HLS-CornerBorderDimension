
#include "tb_utils.h"

void load_image(char* path, xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _out){
	cv::Mat in_img;


	/*  reading in the image  */
	in_img = cv::imread(path,0);

	if (in_img.data == NULL)
	{
		fprintf(stderr,"Cannot open image at %s\n",path);
		return;
	}

	_out.copyTo(in_img.data);
}

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

void step_executer(xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _src, xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _out, int start_step, int end_step){
	if (start_step > end_step){
		std::cout<< "\nERROR: start_step must be less or equal than end_step\n\n";
		return;
	}
	static xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> step1, step2, step3, step4, step5;
	//step 1
	step1.copyTo(_src.data);

	//step 2
	if ((start_step <= 2) && (end_step >= 2))
		step_2(step1, step2);
	else
		step2.copyTo(step1.data);

	//step 3
	if ((start_step <= 3) && (end_step >= 3))
		step_3(step2, step3);
	else
		step3.copyTo(step2.data);

	//step 4
	if ((start_step <= 4) && (end_step >= 4))
		step_4(step3, step4);
	else
		step4.copyTo(step3.data);

	//step 5
	if ((start_step <= 5) && (end_step >= 5))
		step_5(step4, step5);
	else
		step5.copyTo(step4.data);

	_out.copyTo(step5.data);
}
