

#ifndef _XF_EROSION_CONFIG_H_
#define _XF_EROSION_CONFIG_H_

#include "imgproc/xf_erosion.hpp"
#include "xf_config_params.h"

/*
#define FILTER_SIZE 5 //original 3
#define KERNEL_SHAPE XF_SHAPE_ELLIPSE //original XF_SHAPE_CROSS
#define ERODE_ITERATIONS 3
*/

/* CEMVA_IMAGES */
#define ERODE_FILTER_SIZE 7
#define ERODE_KERNEL_SHAPE XF_SHAPE_ELLIPSE
#define ERODE_ITERATIONS 1
/**/

/*  define the input and output types  */
#define NPIX_ERODE NPIX


#define TYPE XF_8UC1

void erosion_accel(xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_ERODE> &_src,xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_ERODE> &_dst);
#endif // _XF_EROSION_CONFIG_H_


