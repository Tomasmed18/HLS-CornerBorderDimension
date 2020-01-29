#include "common_config.h"

struct point{
	ap_uint<COORDINATE_BITS> x;
	ap_uint<COORDINATE_BITS> y;
};

point pixel_remap(ap_uint<COORDINATE_BITS> x, ap_uint<COORDINATE_BITS> y);
