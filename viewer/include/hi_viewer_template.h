/* 
 * File:   hi_viewer_template.h
 * Author: ooaho
 *
 * Created on 2014/03/14, 13:39
 */

#ifndef HI_VIEWER_TEMPLATE_H
#define	HI_VIEWER_TEMPLATE_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstring>

namespace hi{
	template <class T>
	class Viewer{
		public:
			int view;
			Viewer(){};
			//Viewer(const char* wname_in, T* pt_in){ this->prev = 0; this->initialize(wname_in, pt_in); };
			virtual ~Viewer(){ this->vswitch(0); };
			virtual void vswitch(const int& curr){
				if(curr != this->prev){
					if( this->prev == 0 ) this->create();
					else this->destroy();
					this->prev = curr;
				}
				if(curr != 0){
					//cv::namedWindow(this->wname, CV_WINDOW_AUTOSIZE|CV_GUI_NORMAL);
					#if (!defined WIN32) || (!defined WIN64)
			        	cvStartWindowThread();
				    #endif
					this->show();
					cv::waitKey(1);
				}
			};
			virtual void vswitch(){
				this->vswitch(this->view);
			};
			virtual bool initialize(const char* wname_in, T* pt_in){
				this->pt = pt_in; this->wname = wname_in;
				if(this->prev == 1){ cv::destroyWindow(this->wname); }
				this->prev = 0;
				return true;
			};
			virtual void reset(T* pt_in){ this->pt = pt_in; };
		protected:
			int prev;
			const char* wname;
			T* pt;
			virtual void create(){
					std::cout<<this->wname<<" viewer ON "<<std::endl;
					cv::namedWindow(this->wname, CV_WINDOW_AUTOSIZE|CV_GUI_NORMAL);
					//cv::namedWindow(this->wname, CV_WINDOW_AUTOSIZE);
				};
			virtual void destroy(){
					std::cout<<this->wname<<" viewer OFF "<<std::endl;
					cv::destroyWindow(this->wname);
				};
			virtual void show()=0;
	};
}
#endif	/* HI_VIEWER_TEMPLATE_H */

