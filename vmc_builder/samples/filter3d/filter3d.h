#ifndef HI_USBCAMERA_H
#define HI_USBCAMERA_H

#include "hi_model_template.h"
#include "hi_matviewer.h"
#include <vector>
#include <deque>

namespace hi{
	class filter3d : public hi::VModelBase{
	  public:
		cv::Mat input;
		cv::Mat output;
		cv::Mat kmat;
	  	filter3d(){};
	  	virtual ~filter3d(){};
	  	virtual void create();
	  	virtual void execute();
	  	virtual void first_execute();
	  	virtual void release();
	  protected:
		int t;
		int type;
		cv::Range rg[3];
		std::vector<cv::Mat> vec_kmat;
		std::vector<cv::Mat>::iterator it_kmat;
		std::deque<cv::Mat> deq_input;
		std::deque<cv::Mat>::iterator it_input;
		cv::Mat output_elem;
	};
	
/*	class Mat3dIterator{
		//friend cv::Mat;
	private:
		size_t m_index;
		cv::Mat* mat3d;
		cv::Mat mat2d;
		cv::Range rg[3];
		Mat3dIterator(cv::Mat* mat3d_in, int index){
			mat3d = mat3d_in;
			mat2d.create((*mat3d).size[1], (*mat3d).size[2], (*mat3d).type());
			mat2d.data = 
		};
	public:
		static Mat3dIterator begin(const cv::Mat& mat);
		static Mat3dIterator end(const cv::Mat& mat);
		
		const cv::Mat& operator*() const;
		cv::Mat& operator*(){ return mat2d;}; 
		//const cv::Mat& operator->() const;
		//cv::Mat& operator->();
		
		iterator& operator++();
		iterator operator++(int);
		
		iterator& operator+=(size_t n);
		iterator operator+(size_t n);
	};*/
}

#endif // HI_USBCAMERA_H

