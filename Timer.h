#ifndef TIMER_H
#define TIMER_H

#include <SFML\Graphics.hpp>

using namespace std;

class Timer
{
private:
	sf::Clock clock; //used to update the elapsed time

	float elapsed_time; //the current elapsed time of the clock
	bool is_paused; //true if the clock is currently paused

public:
	Timer();

	float getElapsedTime(); //returns the current elapsed time

	void update(); //updates the current clock
	void pauseClock(); //pauses the current clock
	void unpauseClock(); //unpauses the current clock
	void restartClock(); //restarts the current clock
};



#endif