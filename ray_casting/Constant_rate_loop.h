#ifndef __CONSTANT_RATE_LOOP_H__
#define __CONSTANT_RATE_LOOP_H__

#include <chrono>

class Constant_rate_loop {
public:
	explicit Constant_rate_loop(double rate);
	~Constant_rate_loop();

	void task_finished(); 

private:
	const int rate;
	std::chrono::time_point<std::chrono::steady_clock> init_t;
	std::chrono::time_point<std::chrono::steady_clock> end_t;
};

#endif