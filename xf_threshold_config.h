
#ifndef _XF_THRESHOLD_CONFIG_H_
#define _XF_THRESHOLD_CONFIG_H_

#include "hls_stream.h"
#include "ap_int.h"

#include "imgproc/xf_threshold.hpp"
#include "xf_config_params.h"

typedef ap_uint<8>      ap_uint8_t;
typedef ap_uint<64>      ap_uint64_t;



#define NPIX_THRESHOLD				NPIX
/*
#define THRESH 91 //89 best  85 original
#define MAXVAL 255
*/

#define THRESH_TYPE XF_THRESHOLD_TYPE_BINARY

/* CEMVA_IMAGES */
#define THRESH 34
#define MAXVAL 255
/**/

void threshold_accel(xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_src,xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_dst);

#endif  // end of _XF_THRESHOLD_CONFIG_H_
