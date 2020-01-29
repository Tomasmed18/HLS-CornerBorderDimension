

#ifndef _XF_EROSION_CONFIG_H_
#define _XF_EROSION_CONFIG_H_

#include "hls_stream.h"
#include "ap_int.h"
#include "common/xf_common.h"
#include "common/xf_utility.h"
#include "imgproc/xf_erosion.hpp"
#include "xf_config_params.h"

#include "common_config.h"

/*
#define FILTER_SIZE 5 //original 3
#define KERNEL_SHAPE XF_SHAPE_ELLIPSE //original XF_SHAPE_CROSS
#define ERODE_ITERATIONS 3
*/

/* CEMVA_IMAGES */
#define FILTER_SIZE 7
#define KERNEL_SHAPE XF_SHAPE_ELLIPSE
#define ERODE_ITERATIONS 1
/**/

/*  define the input and output types  */
#if NO
#define NPC1 XF_NPPC1
#endif

#if RO
#define NPC1 XF_NPPC8
#endif

#define TYPE XF_8UC1

void erosion_accel(xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_src,xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_dst, unsigned char kernel[FILTER_SIZE*FILTER_SIZE]);
#endif // _XF_DILATION_CONFIG_H_


