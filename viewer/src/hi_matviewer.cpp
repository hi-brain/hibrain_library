#include "hi_matviewer.h"
#include <iostream>

hi::MatViewer::MatViewer(){
	prev = 0; min_size[0] = 200; min_size[1] = 200;
};
hi::MatViewer::~MatViewer(){
	mat.release();
};

bool hi::MatViewer::initialize(const char* wname_in, cv::Mat* pt_in){
	pt = pt_in; wname = wname_in; prev = 0;
	if(prev == 1){ cv::destroyWindow(wname); }
	/*if ((*pt).size[0] < min_size[0] || (*pt).size[1] < min_size[1]){
		double ratio = (double) (*pt).size[0]/(*pt).size[1];
		if (ratio > 1){
			r_size[0] = min_size[0]; r_size[1] = (int) ( min_size[1]*ratio );
		} else {
			r_size[1] = min_size[0]; r_size[0] = (int) ( min_size[0]*ratio );
		}
		resizeflg = true;
	} else { resizeflg = false; }*/
	resizeflg = false;
	return true;
};

void hi::MatViewer::show(){
	//mat.create((*pt).size[0], (*pt).size[1], (*pt).type());
	//(*pt).convertTo(mat, CV_64F);
	//cv::normalize(mat, mat, 1, 0, cv::NORM_MINMAX);//cv::NORM_MINMAX);
	//if(resizeflg) cv::resize(mat, mat, cv::Size(r_size[0],r_size[1]),0,0,0);
	cv::imshow(this->wname, *pt);
};
