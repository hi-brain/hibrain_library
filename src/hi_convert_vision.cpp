#include <opencv2/opencv.hpp>
#include "hi_convert_vision.h"
#include "hi-brain.hh"

cv::Mat operator>>(const Vision::Matrix src, cv::Mat& dst){
	int dims[src.div.length()];
	for(int i=0; i < (int)src.div.length(); ++i) dims[i] = (int) src.div[i]; 
		
	if (dst.empty()){
		dst.create((int) src.div.length(), dims, src.type);
	} else if ( dst.size != cv::Mat::MSize(dims) || dst.type() != (int)src.type || dst.total() * dst.elemSize() != (int)src.pixels.length() ){
		dst.release();
		dst.create(src.div.length(), dims, src.type);
	}
	memcpy(dst.data,(void *)&(src.pixels[0]),src.pixels.length());
	return dst;
}
cv::Mat operator<<(cv::Mat& dst, const Vision::Matrix src){ return src>>dst; }

Vision::Matrix operator>>(const cv::Mat src, Vision::Matrix& dst){
	dst.pixels.length(_CORBA_ULong(src.total() * src.elemSize()));
	dst.div.length(src.dims);
	for (int i=0; i< src.dims; ++i) dst.div[i] = src.size[i];
	dst.type = src.type();
	memcpy((void *)&(dst.pixels[0]), src.data, src.total() * src.elemSize());
	return dst;
}
Vision::Matrix operator<<(Vision::Matrix& dst, const cv::Mat src){ return src>>dst; }

