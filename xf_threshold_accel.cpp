
#include "xf_threshold_config.h"

void threshold_accel(xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_src,xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_dst)
{

	xf::Threshold<THRESH_TYPE,XF_8UC1,HEIGHT, WIDTH,NPIX>(_src, _dst,THRESH, MAXVAL);

}
