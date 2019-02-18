#ifndef DELTATIME_h
#define DELTATIME_h
#include <chrono>

class Deltatime {
public: 
	Deltatime();
	~Deltatime();
	//Frame start
	void start();
	//Frame end
	void end();
	//Calculate the delta Time
	double deltaTime();
private: 
	std::chrono::high_resolution_clock timer;
	std::chrono::time_point<std::chrono::steady_clock> now = timer.now();
	std::chrono::time_point<std::chrono::steady_clock> stop = timer.now();
};


#endif