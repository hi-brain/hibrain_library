#include "filter3d.h"

void hi::filter3d::create(){
	rg[1] = cv::Range::all(); rg[2] = cv::Range::all();
	cv::Mat tmp_mat(kmat.size[1], kmat.size[2], kmat.type());
	for (int t=0; t < kmat.size[0]; ++t){
		rg[0] = cv::Range(t,t+1);
		tmp_mat.data = kmat(rg).data;
		vec_kmat.push_back(tmp_mat.clone());
	}
};
void hi::filter3d::execute(){
	deq_input.push_back(input.clone());
	deq_input.pop_front();
	output = cv::Scalar(0);
	for(it_kmat = vec_kmat.begin(), it_input = deq_input.begin(); it_kmat != vec_kmat.end(); it_kmat++, it_input++){
		cv::filter2D(*it_input, output_elem, input.depth(), *it_kmat);
		output += output_elem;
	}
};

void hi::filter3d::first_execute(){
	output.create(input.size[0], input.size[1], input.type());
	for(int t=0; t<kmat.size[0]; t++){
		deq_input.push_back(input.clone());
	}
};

void hi::filter3d::release(){
	deq_input.clear();
	vec_kmat.clear();
	kmat.release();
	input.release();
	output.release();
	output_elem.release();
};
