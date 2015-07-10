#ifndef HI_USBCAMERA_H
#define HI_USBCAMERA_H

#include "hi_model_template.h"
#include <opencv2/opencv.hpp>
#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>
//#include <coil/TimeValue.h>

namespace hi{
	class usbcamera : public hi::VModelBase{
	  public:
	    int device_num;
		cv::Mat input;
		cv::Mat output;
	  	usbcamera();
	  	virtual ~usbcamera();
	  	virtual void create();
	  	virtual void execute();
	  	virtual void first_execute();
	  	virtual void release();
	  protected:
		cv::VideoCapture vc;	// カメラ用メモリ
		coil::TimeValue tm_pre; // for fps
		int count;
	};
}

#endif // HI_USBCAMERA_H

