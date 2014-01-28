#ifndef __CONVERT_TEMPLATE_H__
#define __CONVERT_TEMPLATE_H__

namespace cv {
	class Mat;
}

namespace RTC {
	struct CameraImage;
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


#endif // __CONVERT_TEMPLATE_H__
