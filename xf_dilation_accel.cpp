#include "xf_dilation_config.h"

unsigned char dilation_kernel[DILATE_FILTER_SIZE*DILATE_FILTER_SIZE] =   {0,0,0,0,0,1,0,0,0,0,0,
																			0,0,0,0,0,1,0,0,0,0,0,
																			0,0,0,0,0,1,0,0,0,0,0,
																			1,1,1,1,1,1,1,1,1,1,1,
																			0,0,0,0,0,1,0,0,0,0,0,
																			0,0,0,0,0,1,0,0,0,0,0,
																			0,0,0,0,0,1,0,0,0,0,0};


void dilation_accel(xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_src,xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_dst)
{

	xf::dilate<XF_BORDER_CONSTANT, TYPE ,HEIGHT, WIDTH, DILATE_KERNEL_SHAPE, DILATE_FILTER_SIZE, DILATE_FILTER_SIZE, DILATE_ITERATIONS, NPC1>(_src, _dst, dilation_kernel);

}
