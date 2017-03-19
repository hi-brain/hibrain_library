#ifndef HI_MATVIEW_H
#define HI_MATVIEW_H

#include "hi_viewer_template.h"
#include <opencv2/opencv.hpp>

namespace hi{
	class MatViewer : public Viewer<cv::Mat>{
	public:
		MatViewer();
		virtual ~MatViewer();
		virtual bool initialize(const char* wname_in, cv::Mat* pt_in);
	protected:
	  	virtual void show();
		cv::Mat mat;
		bool resizeflg;
		int min_size[2];
		int r_size[2];
	};
}

#endif // HI_MATVIEW_H

