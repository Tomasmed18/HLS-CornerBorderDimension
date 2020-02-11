#ifndef CORNER_CLASSIFICATION_H_
#define CORNER_CLASSIFICATION_H_

#include "common_config.h"
#include "ap_int.h"
#include "common/xf_params.h"
#include "common/xf_types.h"
#include "common/xf_common.h"
#include "common/xf_utility.h"

#define TYPE XF_8UC1
#define NPC1 8

#define COORDINATE_BITS 11
#define MAX_CORNERS 800

#define MAX_VAL 2047

#define NPIX XF_NPPC8


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


int corner_classification(xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> &_src, ROI & roi);

#endif /* CORNER_CLASSIFICATION_H_ */
