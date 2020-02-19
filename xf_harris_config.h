

#ifndef _XF_HARRIS_CONFIG_H_
#define _XF_HARRIS_CONFIG_H_


#include "features/xf_harris.hpp"
#include "xf_config_params.h"

/*
 * Pack pixels in and write into streams
 */

#define NPIX_HARRIS				NPIX


#define IMGSIZE				WIDTH*HEIGHT

#define BLOCK_SIZE	 5
#define K_SIZE		 7
#define K 			 0.04
#define HARRIS_THRESH	 	 442
#define NMS_RADIUS	 1
#define FILTER_WIDTH 3
#define XF_USE_URAM false


#define IN_TYPE 			ap_uint<8>

void harris_accel(xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_src, xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_dst);

#endif
