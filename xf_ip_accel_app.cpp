#include "xf_ip_accel_app_config.h"

//void remap_accel(xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_src,xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> &_dst);

void ip_accel_app(hls::stream< ap_axiu<8,1,1,1> >& _src,hls::stream< ap_axiu<8,1,1,1> >& _dst)
{
#pragma HLS INTERFACE axis register both  port=_src
#pragma HLS INTERFACE axis register both  port=_dst

	// xf::Mat<TYPE, ORIGINAL_HEIGHT, ORIGINAL_WIDTH, NPC1> imgInput1(ORIGINAL_HEIGHT, ORIGINAL_WIDTH);
	 xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> imgOutput1(HEIGHT, WIDTH);
	 xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> imgOutput2(HEIGHT, WIDTH);


//#pragma HLS stream variable=imgInput1.data dim=1 depth=1
#pragma HLS stream variable=imgOutput1.data dim=1 depth=1
#pragma HLS stream variable=imgOutput2.data dim=1 depth=1
	#pragma HLS dataflow


	xf::AXIvideo2xfMat(_src, imgOutput1);
	//CBD(imgOutput1,imgOutput2);
	xf::xfMat2AXIvideo(imgOutput1, _dst);


}

