#ifndef TB_UTILS_H_
#define TB_UTILS_H_

#include "xf_headers.h"
#include "xf_threshold_config.h"
#include "xf_erosion_config.h"
#include "xf_dilation_config.h"
#include "xf_harris_config.h"
#include "corner_classification.h"
#include "corner_classification_test_code.h"


void load_image(char* path, xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _out);
void step_executer(xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _src, xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _out,
					int start_step, int end_step);



#endif /* TB_UTILS_H_ */
