#include "hi_convert.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <rtm/idl/InterfaceDataTypes.hh>
#include "hi-brain.hh"
#if USE_MATLAB_RUNTIME
	#include <mclmcrrt.h>
	#include <mclcppclass.h>
#endif

// Convert RTC::CameraImage to cv::Mat
cv::Mat operator>>(const RTC::CameraImage src, cv::Mat& dst)
{
	if(dst.empty()){
		if((unsigned)src.width*src.height == src.pixels.length())
			dst.create(cvSize(src.width,src.height),src.bpp);
	}
	if(dst.size().height != src.height || dst.size().width != src.width || dst.type() != src.bpp || dst.size().height * dst.size().width * dst.elemSize() != src.pixels.length())
	{
		dst.release();
		dst.create(cvSize(src.width,src.height),src.bpp);
	}
	memcpy(dst.data,(void *)&(src.pixels[0]),src.pixels.length());
	return dst;
}
cv::Mat operator<<(cv::Mat& dst, const RTC::CameraImage src){ return src>>dst; }

// Convert cv::Mat to RTC::CameraImage
RTC::CameraImage operator>>(const cv::Mat src, RTC::CameraImage& dst)
{
	dst.pixels.length(_CORBA_ULong(src.size().height * src.size().width * src.elemSize()));
	dst.height	= src.size().height;
	dst.width	= src.size().width;
	dst.bpp	= src.type();
	memcpy((void *)&(dst.pixels[0]),src.data,src.size().height * src.size().width * src.elemSize());
	return dst;
}
RTC::CameraImage operator<<(RTC::CameraImage& dst, const cv::Mat src){ return src>>dst; }

// Convert mwArray to cv::Mat
#if USE_MATLAB_RUNTIME
cv::Mat operator>>(const mwArray src, cv::Mat& dst)
{
	mwArray size = src.GetDimensions();
	int src_height = size.Get(1,1);
	int src_width = size.Get(1,2);
	cv::Mat cv_src;

	switch(src.ClassID()){
	case mxINT8_CLASS:
		if(dst.size().height != src_height || dst.size().width != src_width || dst.type() != CV_8S)
			dst.create(cvSize(src_width,src_height),CV_8S);
		cv_src.create(cvSize(src_height,src_width),CV_8S);
		src.GetData((mxInt8*)cv_src.data,src_width*src_height);
		break;

	case mxUINT8_CLASS:
		if(dst.size().height != src_height || dst.size().width != src_width || dst.type() != CV_8U)
			dst.create(cvSize(src_width,src_height),CV_8U);
		cv_src.create(cvSize(src_height,src_width),CV_8U);
		src.GetData((mxUint8*)cv_src.data,src_width*src_height);
		break;

	case mxINT16_CLASS:
		if(dst.size().height != src_height || dst.size().width != src_width || dst.type() != CV_16S)
			dst.create(cvSize(src_width,src_height),CV_16S);
		cv_src.create(cvSize(src_height,src_width),CV_16S);
		src.GetData((mxInt16*)cv_src.data,src_width*src_height);
		break;

	case mxUINT16_CLASS:
		if(dst.size().height != src_height || dst.size().width != src_width || dst.type() != CV_16U)
			dst.create(cvSize(src_width,src_height),CV_16U);
		cv_src.create(cvSize(src_height,src_width),CV_16U);
		src.GetData((mxUint16*)cv_src.data,src_width*src_height);
		break;

	case mxINT32_CLASS:
		if(dst.size().height != src_height || dst.size().width != src_width || dst.type() != CV_32S)
			dst.create(cvSize(src_width,src_height),CV_32S);
		cv_src.create(cvSize(src_height,src_width),CV_32S);
		src.GetData((mxInt32*)cv_src.data,src_width*src_height);
		break;

	case mxUINT32_CLASS:
	case mxINT64_CLASS:
	case mxUINT64_CLASS:
		if(dst.size().height != src_height || dst.size().width != src_width || dst.type() != CV_64F)
			dst.create(cvSize(src_width,src_height),CV_64F);
		cv_src.create(cvSize(src_height,src_width),CV_64F);
		src.GetData((mxDouble*)cv_src.data,src_width*src_height);
		break;

	case mxSINGLE_CLASS:
		if(dst.size().height != src_height || dst.size().width != src_width || dst.type() != CV_32F)
			dst.create(cvSize(src_width,src_height),CV_32F);
		cv_src.create(cvSize(src_height,src_width),CV_32F);
		src.GetData((mxSingle*)cv_src.data,src_width*src_height);
		break;

	case mxDOUBLE_CLASS:
		if(dst.size().height != src_height || dst.size().width != src_width || dst.type() != CV_64F)
			dst.create(cvSize(src_width,src_height),CV_64F);
		cv_src.create(cvSize(src_height,src_width),CV_64F);
		src.GetData((mxDouble*)cv_src.data,src_width*src_height);
		break;

	default:
		std::cerr << "Can not convert mwArray to cv::Mat" << std::endl;
	}
	if(!cv_src.empty())
		cv::transpose(cv_src,dst);
	return dst;
}
cv::Mat operator<<(cv::Mat& dst, const mwArray src){ return src>>dst; }

// Convert cv::Mat to mwArray
mwArray operator>>(const cv::Mat src, mwArray& dst){
	cv::Mat src_t;

	if(src.channels() != 1){
		std::cerr << "src must be 1 channel" << std::endl;
		return dst;
	}
	cv::transpose(src,src_t);

	mwArray size = dst.GetDimensions();
	int dst_height = size.Get(1,1);
	int dst_width = size.Get(1,2);

	switch(src.type()){
	case CV_8S:
		if(src.size().height != dst_height || src.size().width != dst_width || dst.ClassID() != mxINT8_CLASS)
			dst = mwArray(src.size().height,src.size().width,mxINT8_CLASS);
		dst.SetData((signed char*)src_t.data,src_t.size().width*src_t.size().height);
		break;

	case CV_8U:
		if(src.size().height != dst_height || src.size().width != dst_width || dst.ClassID() != mxUINT8_CLASS)
			dst = mwArray(src.size().height,src.size().width,mxUINT8_CLASS);
		dst.SetData((unsigned char*)src_t.data,src_t.size().width*src_t.size().height);
		break;

	case CV_16S:
		if(src.size().height != dst_height || src.size().width != dst_width || dst.ClassID() != mxINT16_CLASS)
			dst = mwArray(src.size().height,src.size().width,mxINT16_CLASS);
		dst.SetData((short*)src_t.data,src_t.size().width*src_t.size().height);
		break;

	case CV_16U:
		if(src.size().height != dst_height || src.size().width != dst_width || dst.ClassID() != mxUINT16_CLASS)
			dst = mwArray(src.size().height,src.size().width,mxUINT16_CLASS);
		dst.SetData((unsigned short*)src_t.data,src_t.size().width*src_t.size().height);
		break;


	case CV_32S:
		if(src.size().height != dst_height || src.size().width != dst_width || dst.ClassID() != mxINT32_CLASS)
			dst = mwArray(src.size().height,src.size().width,mxINT32_CLASS);
		dst.SetData((int*)src_t.data,src_t.size().width*src_t.size().height);
		break;

	case CV_32F:
		if(src.size().height != dst_height || src.size().width != dst_width || dst.ClassID() != mxSINGLE_CLASS)
			dst = mwArray(src.size().height,src.size().width,mxSINGLE_CLASS);
		dst.SetData((float*)src_t.data,src_t.size().width*src_t.size().height);
		break;

	case CV_64F:
		if(src.size().height != dst_height || src.size().width != dst_width || dst.ClassID() != mxDOUBLE_CLASS)
			dst = mwArray(src.size().height,src.size().width,mxDOUBLE_CLASS);
		dst.SetData((double*)src_t.data,src_t.size().width*src_t.size().height);
		break;

	default:
		std::cerr << "Can not convert cv::Mat to mwArray" << std::endl;
	}
	return dst;
}

mwArray operator<<(mwArray& dst, const cv::Mat src){ return src>>dst; }
#endif

// Convert Vision::Matrix to cv::Mat
cv::Mat operator>>(const Vision::Matrix src, cv::Mat& dst){
	int dims[src.div.length()];
	for(int i=0; i < (int)src.div.length(); ++i) dims[i] = (int) src.div[i];

	if (dst.empty()){
		dst.create((int) src.div.length(), dims, src.type);
	//MSize要検証
	} else if ( dst.type() != (int)src.type || dst.total() * dst.elemSize() != src.pixels.length() ){
//	} else if ( dst.size != cv::Mat::MSize(dims) || dst.type() != (int)src.type || dst.total() * dst.elemSize() != src.pixels.length() ){
		dst.release();
		dst.create(src.div.length(), dims, src.type);
	}
	memcpy(dst.data,(void *)&(src.pixels[0]),src.pixels.length());
	return dst;
}
cv::Mat operator<<(cv::Mat& dst, const Vision::Matrix src){ return src>>dst; }

// Convert cv::Mat to Vision::Matrix
Vision::Matrix operator>>(const cv::Mat src, Vision::Matrix& dst){
	dst.pixels.length(_CORBA_ULong(src.total() * src.elemSize()));
	dst.div.length(src.dims);
	for (int i=0; i< src.dims; ++i) dst.div[i] = src.size[i];
	dst.type = src.type();
	memcpy((void *)&(dst.pixels[0]), src.data, src.total() * src.elemSize());
	return dst;
}
Vision::Matrix operator<<(Vision::Matrix& dst, const cv::Mat src){ return src>>dst; }

// Convert RTC::Timed_cvMat to cv::Mat
/*
cv::Mat operator>>(const RTC::Timed_cvMat src, cv::Mat& dst){
}
cv::Mat operator<<(cv::Mat& src, const RTC::Timed_cvMat dst){ return src>>dst; }
// Convert cv::Mat to RTC::Timed_cvMat
RTC::Timed_cvMat operator>>(const cv::Mat src, RTC::Timed_cvMat& dst){
}
RTC::Timed_cvMat operator<<(RTC::Timed_cvMat& src, const cv::Mat dst){ return src>>dst; }
*/
