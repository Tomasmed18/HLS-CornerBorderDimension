

#ifndef _XF_HARRIS_CONFIG_H_
#define _XF_HARRIS_CONFIG_H_


#include "hls_stream.h"
#include "ap_int.h"
#include "common/xf_common.h"
#include "common/xf_utility.h"
#include "features/xf_harris.hpp"
#include "xf_config_params.h"

/*
 * Pack pixels in and write into streams
 */

#if RO
#define NPIX				XF_NPPC8
#endif                      
#if NO                      
#define NPIX				XF_NPPC1
#endif


#include "common_config.h"

#define IMGSIZE				WIDTH*HEIGHT

#define BLOCK_SIZE	 5
#define K_SIZE		 7
#define K 			 0.04
#define THRESH	 	 442
#define NMS_RADIUS	 1
#define FILTER_WIDTH 3
#define XF_USE_URAM false


#if RO
#define IN_TYPE 			ap_uint<64>
#endif
#if NO
#define IN_TYPE 			ap_uint<8>
#endif
void harris_accel(xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_src, xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_dst);

#endif
