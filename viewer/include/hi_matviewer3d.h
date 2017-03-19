/* 
 * File:   hi_matviewer3d.h
 * Author: ooaho
 *
 * Created on 2014/03/20, 14:07
 */

#ifndef HI_MATVIEWER3D_H
#define	HI_MATVIEWER3D_H

#include "hi_viewer_template.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

namespace hi{
	class MatViewer3d : public Viewer<cv::Mat>{
	public:
		MatViewer3d();
		~MatViewer3d();
		bool initialize(const char* wname_in, cv::Mat* pt_in);
	protected:
		//hi::MatViewer3d* spt;
		int slider;
		int slider_max;
		bool resizeflg;
		int min_size[2];
		int r_size[2];
		cv::Mat submat;
		cv::Mat mat;
		cv::Range rg[3];
	  	void show();
		void show_impl( int );
		static void on_trackbar( int, void* );
	};
}


#endif	/* HI_MATVIEWER3D_H */

