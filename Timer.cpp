#include "Timer.h"

Timer::Timer()
{
	this->is_paused = false;
	this->elapsed_time = 0.0;
	this->clock.restart();
}

float Timer::getElapsedTime()
{
	return( this->elapsed_time );
}

void Timer::update()
{
	if( this->is_paused == false ) //only updates clock if it is not paused
	{
		this->elapsed_time += this->clock.getElapsedTime().asSeconds();
		this->clock.restart(); //resets clock for next update
	}
}

void Timer::pauseClock()
{
	this->is_paused = true; //pauses the current clock
}

void Timer::unpauseClock()
{
	this->clock.restart();
	this->is_paused = false; //unpauses the current clock
}

void Timer::restartClock()
{
	this->clock.restart();
	this->elapsed_time = 0.0;
}

