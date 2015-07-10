#include "cv_retina.h"

hi::cvRetina::cvRetina(){};
hi::cvRetina::~cvRetina(){};

void hi::cvRetina::create(){};

void hi::cvRetina::execute(){
	retina->run(input);
	retina->getParvo(parvo);
	retina->getMagno(magno);
};

void hi::cvRetina::first_execute(){
	retina.release();
	parvo.release();
	magno.release();
	if(log_sampling == 0){
		retina = new cv::Retina(input.size());
	} else {
		retina = new cv::Retina(input.size(), true, cv::RETINA_COLOR_BAYER, true, 2.0, 10.0);
	}
}

void hi::cvRetina::release(){
	input.release();
	retina.release();
	parvo.release();
	magno.release();
};
