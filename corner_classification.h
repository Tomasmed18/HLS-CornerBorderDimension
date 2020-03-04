#ifndef CORNER_CLASSIFICATION_H_
#define CORNER_CLASSIFICATION_H_

#include "common/xf_structs.h" //for xf::Mat class

#include "xf_headers.h"
#include "xf_config_params.h"

#define TYPE 0 //XF_8UC1
//#define NPC1 8

#define COORDINATE_BITS 11
#define MAX_CORNERS 2000

#define MAX_VAL 2047

#define NPIX_CORNER_CLASSIFICATION NPIX //XF_NPPC1

//drawing colors
#define CORNER_COLOR 0xFF00AA
#define CORRECT_BORDER_COLOR 0x47E541
#define ERROR_BORDER_COLOR 0xF0FF00

//handicaps
#define HANDICAP_CORNER 20
#define HANDICAP_ERROR 20

//dimension verification
#define MIN_AREA 800000
#define MAX_AREA 900000


//result codes
#define NO_ERROR 0
#define CORNER_ERROR 1
#define BORDER_ERROR 2
#define DIMENSION_ERROR 3


int corner_classification(xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_CORNER_CLASSIFICATION> &_src, xf::Mat<XF_8UC3, HEIGHT, WIDTH, NPIX_CORNER_CLASSIFICATION> &_dst, ROI & roi);

#endif /* CORNER_CLASSIFICATION_H_ */
