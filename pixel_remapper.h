//#include "xf_config_params.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_math.h" //round() function

#define COORDINATE_BITS 11

struct point{
	ap_uint<COORDINATE_BITS> x;
	ap_uint<COORDINATE_BITS> y;
};

point pixel_remap(ap_uint<COORDINATE_BITS> x, ap_uint<COORDINATE_BITS> y);

//void pixel_remap_test();
