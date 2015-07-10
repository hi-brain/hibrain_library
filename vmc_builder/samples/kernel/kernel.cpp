#include "kernel.h"
#include <cmath>

void hi::kernel3d::create(){
  if(type == "Sobel"){
	size[0] = 3; size[1] = 3; size[2] = 3;
    std::cout << size[0] << "x" << size[1] << "x" << size[2] << " " << type << " for the " << dimension << "-derivative" << std::endl;
	kmat.create(3, size, CV_64FC1);
	cv::Mat subkmat(size[1], size[2], CV_64FC1);
	cv::Range rg[3] = {cv::Range(0,1), cv::Range::all(), cv::Range::all()};
	/*for (int t = 0; t<size[0]; ++t){
		rg[0] = cv::Range(t,t+1);
		submat.data = kmat(rg).data;
    */
    if(dimension == "X"){
      submat = (cv::Mat_<double>(size[1],size[2]) << 1,0,-1,2,0,-2,1,0,-1);
      rg[0] = cv::Range(0,1); memcpy(kmat(rg).data, submat.data, submat.total()*submat.elemSize());
      rg[0] = cv::Range(2,3); memcpy(kmat(rg).data, submat.data, submat.total()*submat.elemSize());
      submat = (cv::Mat_<double>(size[1],size[2]) << 2,0,-2,4,0,-4,2,0,-2);
      rg[0] = cv::Range(1,2); memcpy(kmat(rg).data, submat.data, submat.total()*submat.elemSize());
    } else if(dimension == "Y"){
      submat = (cv::Mat_<double>(size[1],size[2]) << -1,-2,-1,0,0,0,1,2,1);
      rg[0] = cv::Range(0,1); memcpy(kmat(rg).data, submat.data, submat.total()*submat.elemSize());
      rg[0] = cv::Range(2,3); memcpy(kmat(rg).data, submat.data, submat.total()*submat.elemSize());
      submat = (cv::Mat_<double>(size[1],size[2]) << -2,-4,-2,0,0,0,2,4,2);
      rg[0] = cv::Range(1,2); memcpy(kmat(rg).data, submat.data, submat.total()*submat.elemSize());
    } else if(dimension == "T"){
      submat = (cv::Mat_<double>(size[1],size[2]) << 1,2,1,2,4,2,1,2,1);
      rg[0] = cv::Range(0,1); memcpy(kmat(rg).data, submat.data, submat.total()*submat.elemSize());
      submat = (cv::Mat_<double>(size[1],size[2]) << 0,0,0,0,0,0,0,0,0);
      rg[0] = cv::Range(1,2); memcpy(kmat(rg).data, submat.data, submat.total()*submat.elemSize());
      submat = (cv::Mat_<double>(size[1],size[2]) << -1,-2,-1,-2,-4,-2,-1,-2,-1);
      rg[0] = cv::Range(2,3); memcpy(kmat(rg).data, submat.data, submat.total()*submat.elemSize());
    }
    kmat = kmat/4;
    submat.release();
  } else if(type == "Gabor") {
	std::cout << type << " for the " << dimension << "-derivative" << std::endl;
    //getGaborKernel(Size ksize, double sigma, double theta, double lambd, double gamma, double psi=CV_PI*0.5, int ktype=CV_64F )
	cv::Range rg[3] = {cv::Range(0,1), cv::Range::all(), cv::Range::all()};
    if(dimension == "X"){
		size[0] = 1; size[1] = 21; size[2] = 21;
		kmat.create(3, size, CV_64FC1);
		submat.create(size[1], size[2], CV_64FC1);
		submat = cv::getGaborKernel(cv::Size(size[1],size[2]), 5, 0, 19, 1);
		rg[0] = cv::Range(0,1);
		memcpy(kmat(rg).data, submat.data, submat.total()*submat.elemSize());
    } else if(dimension == "Y"){
		size[0] = 1; size[1] = 21; size[2] = 21;
		kmat.create(3, size, CV_64FC1);
		submat.create(size[1],size[2], CV_64FC1);
		submat = cv::getGaborKernel(cv::Size(size[1],size[2]), 5, CV_PI*0.5, 19, 1);
		rg[0] = cv::Range(0,1); memcpy(kmat(rg).data, submat.data, submat.total()*submat.elemSize());
    } else if(dimension == "T"){
		size[0] = 21; size[1] = 1; size[2] = 1;
		kmat.create(3, size, CV_64FC1);
		cv::MatIterator_<double> it = kmat.begin<double>();
		for(int t = -10; it!=kmat.end<double>(); it++, t++) {
			*it = sqrt(1.0/(2.0*CV_PI*5.0))*cos(2.0*CV_PI*t/19.0 + CV_PI*0.5)*exp(-(t*t)/50.0);
		}
    }
    submat.release();
  }
};

void hi::kernel3d::release(){
	kmat.release();
};
