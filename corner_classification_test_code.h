#ifndef CORNER_CLASSIFICATION_TEST_CODE_H_
#define CORNER_CLASSIFICATION_TEST_CODE_H_

#include "xf_headers.h"
#include "corner_classification.h"


ROI corner_classification_testing(xf::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> & _src, cv::Mat & _image_to_draw);

ROI corner_classification_testing_2(xf::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> & _src, cv::Mat & _image_to_draw);

#endif /* CORNER_CLASSIFICATION_TEST_CODE_H_ */
