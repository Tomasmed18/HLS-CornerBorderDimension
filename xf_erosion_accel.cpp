#include "xf_erosion_config.h"

unsigned char erode_kernel[ERODE_FILTER_SIZE*ERODE_FILTER_SIZE] ={0,0,0,1,0,0,0,
												0,0,0,1,0,0,0,
												0,0,0,1,0,0,0,
												1,1,1,1,1,1,1,
												0,0,0,1,0,0,0,
												0,0,0,1,0,0,0,
												0,0,0,1,0,0,0};



void erosion_accel(xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_src,xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_dst)
{

	xf::erode<XF_BORDER_CONSTANT, TYPE ,HEIGHT, WIDTH, ERODE_KERNEL_SHAPE, ERODE_FILTER_SIZE, ERODE_FILTER_SIZE, ERODE_ITERATIONS, NPC1>(_src, _dst,erode_kernel);

}
