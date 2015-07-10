#ifndef HI_USBCAMERA_H
#define HI_USBCAMERA_H

#include "hi_model_template.h"
#include "hi_matviewer.h"

namespace hi{
	class kernel3d : public hi::VModelBase{
	  public:
		std::string type;
		std::string dimension;
		cv::Mat kmat;
	  	kernel3d(){};
	  	virtual ~kernel3d(){};
	  	virtual void create();
	  	virtual void execute(){};
	  	virtual void first_execute(){};
	  	virtual void release();
	  protected:
		cv::Mat submat;
		int size[3];
	};
}

#endif // HI_USBCAMERA_H

