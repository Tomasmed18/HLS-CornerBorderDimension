#include "xf_ip_accel_config.h"

// CBD STEPS
#include "xf_threshold_config.h"
#include "xf_erosion_config.h"
#include "xf_dilation_config.h"
#include "xf_harris_config.h"
#include "imgproc/xf_cvt_color.hpp"
#include "corner_classification.h"

void cbd_accel(hls::stream< ap_axiu<24,1,1,1> >& _src,hls::stream< ap_axiu<8,1,1,1> >& _dst)
{
#pragma HLS INTERFACE axis register both  port=_src
#pragma HLS INTERFACE axis register both  port=_dst

	 xf::Mat<XF_8UC3, HEIGHT, WIDTH, NPIX_CDB> imgOutput0(HEIGHT, WIDTH);
	 xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_CDB> imgOutput1(HEIGHT, WIDTH);
	 xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_CDB> img_u(HEIGHT, WIDTH);
	 xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_CDB> img_v(HEIGHT, WIDTH);
	 xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_CDB> imgOutput2(HEIGHT, WIDTH);
	 xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_CDB> imgOutput3(HEIGHT, WIDTH);
	 xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_CDB> imgOutput4(HEIGHT, WIDTH);
	 xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_CDB> imgOutput5(HEIGHT, WIDTH);

	 ROI roi;


#pragma HLS stream variable=imgOutput0.data dim=1 depth=1
#pragma HLS stream variable=imgOutput1.data dim=1 depth=1
#pragma HLS stream variable=imgOutput2.data dim=1 depth=1
#pragma HLS stream variable=imgOutput3.data dim=1 depth=1
#pragma HLS stream variable=imgOutput4.data dim=1 depth=1
#pragma HLS stream variable=imgOutput5.data dim=1 depth=1
	#pragma HLS dataflow


	xf::AXIvideo2xfMat(_src, imgOutput0);

	//RGB to YUV conversion, to obtain the grayscale image
	xf::rgb2yuv4<XF_8UC3,XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>(imgOutput0,imgOutput1,img_u,img_v);
	threshold_accel(imgOutput1, imgOutput2);
	erosion_accel(imgOutput2, imgOutput3);
	dilation_accel(imgOutput3, imgOutput4);
	harris_accel(imgOutput4, imgOutput5);
	int result = corner_classification(imgOutput5, roi);

	xf::xfMat2AXIvideo(imgOutput5, _dst);


}
