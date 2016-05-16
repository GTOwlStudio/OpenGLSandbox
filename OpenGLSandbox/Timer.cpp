#include "Timer.h"

Timer::Timer(uint32_t duration) : m_duration(duration), m_stime(0), m_elapsedTime(0), m_isElapsed(false)
{
}

Timer::~Timer()
{
}

void Timer::start() {
	m_stime = clock();
}

void Timer::update() {
	m_elapsedTime = clock() - m_stime;
	m_stime = clock();
	if (m_elapsedTime>=m_duration) {
		m_isElapsed = true;
	}
}

bool Timer::isElapsed()
{
	return m_elapsedTime;
}

