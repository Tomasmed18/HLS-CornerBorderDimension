#include "common_config.h"

struct point{
	//ap_uint<COORDINATE_BITS> x;
	//ap_uint<COORDINATE_BITS> y;
	float x, y;
};

point pixel_remap(int x, int y);

void pixel_remap_test();
