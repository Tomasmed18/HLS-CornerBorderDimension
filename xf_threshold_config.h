
#ifndef _XF_THRESHOLD_CONFIG_H_
#define _XF_THRESHOLD_CONFIG_H_

#include "hls_stream.h"
#include "ap_int.h"

#include "common/xf_common.h"
#include "common/xf_utility.h"

#include "imgproc/xf_threshold.hpp"
#include "xf_config_params.h"

typedef ap_uint<8>      ap_uint8_t;
typedef ap_uint<64>      ap_uint64_t;


#include "common_config.h"

#if RO
#define NPIX				XF_NPPC8
#endif                      
#if NO                      
#define NPIX				XF_NPPC1
#endif
/*
#define THRESH 91 //89 best  85 original
#define MAXVAL 255
*/

/* CEMVA_IMAGES */
#define THRESH 34
#define MAXVAL 255
/**/

void threshold_accel(xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_src,xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_dst);

#endif  // end of _XF_THRESHOLD_CONFIG_H_
