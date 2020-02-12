#ifndef _COMMON_CONFIG_
#define _COMMON_CONFIG_

#include "xf_headers.h"

#define HEIGHT 1080
#define WIDTH 1920
#define COORDINATE_BITS 11

struct ROI{
	ap_uint<COORDINATE_BITS> x1;
	ap_uint<COORDINATE_BITS> y1;
	ap_uint<COORDINATE_BITS> x2;
	ap_uint<COORDINATE_BITS> y2;
	ap_uint<COORDINATE_BITS> x3;
	ap_uint<COORDINATE_BITS> y3;
	ap_uint<COORDINATE_BITS> x4;
	ap_uint<COORDINATE_BITS> y4;
};



#endif
