#ifndef HI_USBCAMERA_H
#define HI_USBCAMERA_H

#include "hi_model_template.h"
#include "hi_matviewer.h"

namespace hi{
	class cvRetina : public hi::VModelBase{
	  public:
		int log_sampling;
		cv::Mat input;
		cv::Mat magno;
		cv::Mat parvo;
	  	cvRetina();
	  	virtual ~cvRetina();
	  	virtual void create();
	  	virtual void execute();
	  	virtual void first_execute();
	  	virtual void release();
	  protected:
		cv::Ptr<cv::Retina> retina;
	};
}

#endif // HI_USBCAMERA_H

