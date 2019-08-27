
#include "xf_harris_config.h"

void harris_accel(xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_src, xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_dst)
{	
    xf::cornerHarris<FILTER_WIDTH,BLOCK_SIZE,NMS_RADIUS,XF_8UC1,HEIGHT,WIDTH,NPIX,XF_USE_URAM>(_src, _dst, THRESH, K);
}
