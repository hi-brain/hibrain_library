#include "hi_convert.h"
#include <iostream>
//#include <opencv2\core\core.hpp>
#include "opencv2/opencv.hpp"
#include <mclmcrrt.h>
#include <mclcppclass.h>
#include <rtm/idl/InterfaceDataTypes.hh>

cv::Mat operator>>(const RTC::CameraImage src, cv::Mat& dst)
{
	if(dst.empty()){
		if((unsigned)src.width*src.height == src.pixels.length())
			dst.create(cvSize(src.width,src.height),src.bpp);
	}
	if(dst.size().height != src.height || dst.size().width != src.width || dst.type() != src.bpp || dst.size().height * dst.size().width * dst.elemSize() != (int)src.pixels.length())
	{
		dst.release();
		dst.create(cvSize(src.width,src.height),src.bpp);
	}
	memcpy(dst.data,(void *)&(src.pixels[0]),src.pixels.length());
	return dst;
}


//inputFrame<<m_input
cv::Mat operator<<(cv::Mat& dst, const RTC::CameraImage src)
{
	return src>>dst;
}


//outputFrame>>m_output
RTC::CameraImage operator>>(const cv::Mat src, RTC::CameraImage& dst)
{
	dst.pixels.length(_CORBA_ULong(src.size().height * src.size().width * src.elemSize()));
	dst.height	= src.size().height;
	dst.width	= src.size().width;
	dst.bpp	= src.type();
	memcpy((void *)&(dst.pixels[0]),src.data,src.size().height * src.size().width * src.elemSize());
	return dst;
}


//m_output<<outputFrame
RTC::CameraImage operator<<(RTC::CameraImage& dst, const cv::Mat src)
{
	return src>>dst;
}


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

		// mxUINT32_CLASS, mxINT64_CLASS, mxUINT64_CLASS ÇÕëŒâûÇ∑ÇÈCVÇÃå^Ç™Ç»Ç¢ÇÃÇ≈ CV_64F Ç…âüÇµçûÇﬁ
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


cv::Mat operator<<(cv::Mat& dst, const mwArray src)
{
	return src>>dst;
}


mwArray operator>>(const cv::Mat src, mwArray& dst){
	cv::Mat src_t;

	if(src.channels() != 1){
		std::cerr << "src must be 1 channel" << std::endl;
		return dst;
	}
	cv::transpose(src,src_t);

	// ãÛÇÃèÍçáÇÕ0,0Ç™ì¸ÇÈ
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


mwArray operator<<(mwArray& dst, const cv::Mat src){
	return src>>dst;
}

