#pragma once
#include <stdint.h>
#include <time.h>
#include "EventManager.h"
class Timer
{
public:
	Timer(uint32_t duration);
	~Timer();
	void start();
	void stop();
	void update();
	bool isRunning();
	bool isElapsed();



private:
	uint32_t m_stime; //time since last run;
	uint32_t m_elapsedTime;//Elapsed time since start
	uint32_t m_duration;
	bool m_isElapsed;
	EventManager m_mng;

};

