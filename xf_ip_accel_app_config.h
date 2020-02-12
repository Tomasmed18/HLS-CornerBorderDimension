
#ifndef _XF_IP_ACCEL_APP_CONFIG_H_
#define _XF_IP_ACCEL_APP_CONFIG_H_

#include "common_config.h"
#include "xf_config_params.h"

#if NO
#define NPC1 XF_NPPC1
#endif

#if RO
#define NPC1 XF_NPPC8
#endif

#define TYPE XF_8UC1

void ip_accel_app(hls::stream< ap_axiu<8,1,1,1> >& _src,hls::stream< ap_axiu<8,1,1,1> >& _dst);

#endif // _XF_IP_ACCEL_APP_CONFIG_H_
