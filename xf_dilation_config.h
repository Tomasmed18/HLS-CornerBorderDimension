

#ifndef _XF_DILATION_CONFIG_H_
#define _XF_DILATION_CONFIG_H_

#include "imgproc/xf_dilation.hpp"
#include "xf_config_params.h"

/*
#define FILTER_SIZE 5
#define KERNEL_SHAPE XF_SHAPE_CROSS
#define DILATE_ITERATIONS 3
*/

/* CEMVA_IMAGES */
#define DILATE_FILTER_SIZE 11
#define DILATE_KERNEL_SHAPE XF_SHAPE_ELLIPSE
#define DILATE_ITERATIONS 10
/**/

/*  define the input and output types  */
#define NPIX_DILATE NPIX


#define TYPE XF_8UC1

void dilation_accel(xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_DILATE> &_src,xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_DILATE> &_dst);
#endif // _XF_DILATION_CONFIG_H_


