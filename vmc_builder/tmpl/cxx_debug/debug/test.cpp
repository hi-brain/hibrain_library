#include "filter3d.h"
#include <iostream>

void setconfig(hi::filter3d &obj){};

void input_onActivated(hi::filter3d &obj){
	int size[] = {3,3,3};
	obj.kmat.create(3, size, CV_64FC1);
	cv::Mat subkmat(3, 3, CV_64FC1);
	cv::Range rg[3] = {cv::Range(0,1), cv::Range::all(), cv::Range::all()};
	subkmat = (cv::Mat_<double>(size[1],size[2]) << 1,0,-1,2,0,-2,1,0,-1);
	rg[0] = cv::Range(0,1); memcpy(obj.kmat(rg).data, subkmat.data, subkmat.total()*subkmat.elemSize());
	rg[0] = cv::Range(2,3); memcpy(obj.kmat(rg).data, subkmat.data, subkmat.total()*subkmat.elemSize());
	subkmat = (cv::Mat_<double>(size[1],size[2]) << 2,0,-2,4,0,-4,2,0,-2);
	rg[0] = cv::Range(1,2); memcpy(obj.kmat(rg).data, subkmat.data, subkmat.total()*subkmat.elemSize());
};
void input_onExecute(hi::filter3d &obj){
	obj.input = cv::imread("img/lenna.png", 1);
};
void input_onDeactivated(hi::filter3d &obj){};

int main(){
	hi::filter3d obj;
	hi::MatViewer viewer_output;
	
	setconfig(obj);
	
	std::cout << "onActivated" << std::endl;
	input_onActivated(obj);
	obj.create();
	
	viewer_output.initialize("output", &obj.output);
	
	std::cout << "onExecute" << std::endl;
	input_onExecute(obj);
	std::cout << "first_execute()" << std::endl;
	obj.first_execute();
	std::cout << "execute()" << std::endl;
	obj.execute();
	
	//std::cout << obj.output << std::endl;
	viewer_output.vswitch(1);
	//cv::imshow("output", obj.output);
	std::cout << "Plz press any key (on viewer window)" << std::endl;
	cv::waitKey(0);
	
	std::cout << "onDeactivated" << std::endl;
	input_onDeactivated(obj);
	obj.release();
	
	return 0;
}
