/*
 * File:   hi_convert.h
 * Author: Kazuki Urabe, ooaho
 *
 * Created on 2015/07/06, 22:21
 */

#ifndef __CONVERT_TEMPLATE_H__
#define __CONVERT_TEMPLATE_H__

namespace cv {
	class Mat;
}
namespace RTC {
	struct Timed_cvMat;
	struct CameraImage;
}
namespace Vision{
	class Matrix;
}
class mwArray;

// Convert RTC::CameraImage to cv::Mat
cv::Mat operator>>(const RTC::CameraImage src, cv::Mat& dst);
cv::Mat operator<<(cv::Mat& dst, const RTC::CameraImage src);
//__declspec(dllexport) cv::Mat operator>>(const RTC::CameraImage src, cv::Mat& dst);
//__declspec(dllexport) cv::Mat operator<<(cv::Mat& dst, const RTC::CameraImage src);

// Convert cv::Mat to RTC::CameraImage
RTC::CameraImage operator>>(const cv::Mat src, RTC::CameraImage& dst);
RTC::CameraImage operator<<(RTC::CameraImage& dst, const cv::Mat src);
//__declspec(dllexport) RTC::CameraImage operator>>(const cv::Mat src, RTC::CameraImage& dst);
//__declspec(dllexport) RTC::CameraImage operator<<(RTC::CameraImage& dst, const cv::Mat src);

// Convert mwArray to cv::Mat
cv::Mat operator>>(const mwArray src, cv::Mat& dst);
cv::Mat operator<<(cv::Mat& dst, const mwArray src);
//__declspec(dllexport) cv::Mat operator>>(const mwArray src, cv::Mat& dst);
//__declspec(dllexport) cv::Mat operator<<(cv::Mat& dst, const mwArray src);

// Convert cv::Mat to mwArray
mwArray operator>>(const cv::Mat src, mwArray& dst);
mwArray operator<<(mwArray& dst, const cv::Mat src);
//__declspec(dllexport) mwArray operator>>(const cv::Mat src, mwArray& dst);
//__declspec(dllexport) mwArray operator<<(mwArray& dst, const cv::Mat src);

// Convert Vision::Matrix to cv::Mat
cv::Mat operator>>(const Vision::Matrix src, cv::Mat& dst);
cv::Mat operator<<(cv::Mat& dst, const Vision::Matrix src);
//__declspec(dllexport) cv::Mat operator>>(const Vision::Matrix src, cv::Mat& dst);
//__declspec(dllexport) cv::Mat operator<<(cv::Mat& dst, const Vision::Matrix src);

// Convert cv::Mat to Vision::Matrix
Vision::Matrix operator>>(const cv::Mat src, Vision::Matrix& dst);
Vision::Matrix operator<<(Vision::Matrix& dst, const cv::Mat src);
//__declspec(dllexport) Vision::Matrix operator>>(const cv::Mat src, Vision::Matrix& dst);
//__declspec(dllexport) Vision::Matrix operator<<(Vision::Matrix& dst, const cv::Mat src);

// Convert RTC::Timed_cvMat to cv::Mat
/*
cv::Mat operator>>(const RTC::Timed_cvMat src, cv::Mat& dst);
cv::Mat operator<<(cv::Mat& src, const RTC::Timed_cvMat dst);
// Convert cv::Mat to RTC::Timed_cvMat
RTC::Timed_cvMat operator>>(const cv::Mat src, RTC::Timed_cvMat& dst);
RTC::Timed_cvMat operator<<(RTC::Timed_cvMat& src, const cv::Mat dst);
*/
#endif // __CONVERT_TEMPLATE_H__
