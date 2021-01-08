#include "Constant_rate_loop.h"
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <iostream>

Constant_rate_loop::Constant_rate_loop(const double rate) : 
										rate(rate), 
										init_t(std::chrono::steady_clock::now()), 
										end_t(std::chrono::steady_clock::now()) {
}

Constant_rate_loop::~Constant_rate_loop() {
}

void Constant_rate_loop::task_finished() {
	this->end_t = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff = this->end_t - this->init_t;
	double rest = ((double) this->rate) / 1000 - diff.count();
	//std::cout << rest << std::endl; 

	if (rest < 0) {
		int behind = - rest * 1000;
		int lost =  behind - behind % rate;
		this->init_t = this->init_t + std::chrono::milliseconds(lost);

	} else {
		sleep(rest);
	}
	this->init_t = this->init_t + std::chrono::milliseconds(this->rate);
}