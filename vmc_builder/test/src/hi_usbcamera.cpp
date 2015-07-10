#include "hi_usbcamera.h"
#include <iostream>

hi::usbcamera::usbcamera(){};
hi::usbcamera::~usbcamera(){};

void hi::usbcamera::create(){
	this->count=0;
	this->vc.open(device_num);
	if (!this->vc.isOpened()){
		std::cout<<"No Camera Device"<<std::endl;
		this->st = false;
	}
};

void hi::usbcamera::execute(){
	if (!this->vc.isOpened() || !this->vc.read(this->output)) return;
	if (this->count > 100){
		this->count = 0;
		coil::TimeValue tm = coil::gettimeofday();
		double sec(tm - tm_pre);
		if (sec > 1.0 && sec < 1000.0) std::cout << 100/sec << " [FPS]" << std::endl;
		this->tm_pre = tm;
	}
	++this->count;
};

void hi::usbcamera::first_execute(){}

void hi::usbcamera::release(){
	input.release();
	output.release();
	this->vc.release();
	this->count = 0;
	this->st = true;
};
