#include "Deltatime.h"
using ms = std::chrono::duration<float, std::milli>;

Deltatime::Deltatime() {
	
}

Deltatime::~Deltatime() {

}

void Deltatime::start() {
	this->now = this->timer.now();
}

void Deltatime::end() {
	this->stop = this->timer.now();
}

double Deltatime::deltaTime() {
	std::chrono::duration<double> dt = stop - now;
	double deltaTime = std::chrono::duration_cast<ms>(stop - now).count() / 1000;

	return deltaTime;
}
