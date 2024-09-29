#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL2/SDL.h>

class Timer {
public:
	Timer();

	void start();
	// Return elapsed time in mili seconds
	Uint32 read();
	// Return elapsed time in seconds
	float readSeconds();
private:
	Uint32 startTicks;
};

#endif // TIMER_HPP