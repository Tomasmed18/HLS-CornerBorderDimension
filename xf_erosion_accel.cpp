

#include "xf_erosion_config.h"

void erosion_accel(xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_src,xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_dst, unsigned char kernel[FILTER_SIZE*FILTER_SIZE])
{

	xf::erode<XF_BORDER_REPLICATE, TYPE ,HEIGHT, WIDTH, KERNEL_SHAPE, FILTER_SIZE, FILTER_SIZE, ERODE_ITERATIONS, NPC1>(_src, _dst,kernel);

}
