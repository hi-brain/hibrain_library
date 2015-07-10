#include "hi_matviewer3d.h"

hi::MatViewer3d::MatViewer3d(){
	prev = 0; min_size[0] = 200; min_size[1] = 200;
};
hi::MatViewer3d::~MatViewer3d(){
	mat.release();
};

bool hi::MatViewer3d::initialize(const char* wname_in, cv::Mat* pt_in){
	if ((*pt_in).dims != 3) return false;
	pt = pt_in; wname = wname_in;
	if(prev == 1){ cv::destroyWindow(wname); }
	submat.create((*pt).size[1], (*pt).size[2], (*pt).type());
	if ((*pt).size[1] < min_size[0] || (*pt).size[2] < min_size[1]){
		double ratio = (double) (*pt).size[1]/(*pt).size[2];
		if (ratio > 1){
			r_size[0] = min_size[0]; r_size[1] = (int) ( min_size[1]*ratio );
		} else {
			r_size[1] = min_size[0]; r_size[0] = (int) ( min_size[0]*ratio );
		}
		resizeflg = true;
	} else { resizeflg = false; }
	rg[0] = cv::Range(0,1); rg[1] = cv::Range::all(); rg[2] = cv::Range::all();
	slider_max = (*pt).size[0] - 1; slider =  0;
	prev = 0;
	return true;
};

void hi::MatViewer3d::show(){
	if(slider_max > 0){
		cv::createTrackbar("index", wname, &slider, slider_max, hi::MatViewer3d::on_trackbar, this);
		on_trackbar(0, this);
	}
	//cmat = vmat->at(slider);
	//cv::normalize(cmat, cmat, 1, 0, cv::NORM_MINMAX);
	//cv::resize(cmat, cmat, cv::Size(size_x,size_y),0,0,0);
	show_impl(0);
};

void hi::MatViewer3d::show_impl( int ){
	rg[0] = cv::Range(slider, slider+1);
	submat.data = (*pt)(rg).data;
	cv::normalize(submat, mat, 1, 0, cv::NORM_MINMAX);
	if(resizeflg) cv::resize(mat, mat, cv::Size(r_size[0],r_size[1]),0,0,0);
	cv::imshow(wname,mat);
}
void hi::MatViewer3d::on_trackbar( int val, void* pt){
	hi::MatViewer3d* spt = reinterpret_cast<hi::MatViewer3d*>(pt);
	spt->show_impl(val);
};


