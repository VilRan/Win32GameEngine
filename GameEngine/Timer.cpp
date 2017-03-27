#include "Timer.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

Timer::Timer()
{
	m_dTimerRateToSeconds = 0.0;
	m_iTickFrequency = 0;
	m_iStartClock = 0;
	m_fElapsedSeconds = 0;
}

Timer::~Timer()
{
}

void Timer::Create()
{
	INT64 rate;
	::QueryPerformanceFrequency((LARGE_INTEGER*)&rate);
	m_dTimerRateToSeconds = 1.0 / (double)rate;
	m_iTickFrequency = rate;
}

void Timer::Start()
{
	::QueryPerformanceCounter((LARGE_INTEGER*)&m_iStartClock);
}

void Timer::Stop()
{
	INT64 ticks;
	::QueryPerformanceCounter((LARGE_INTEGER*)&ticks);

	// compute how many ticks have passed since Start
	ticks = ticks - m_iStartClock;

	if (ticks == m_iStartClock || m_iStartClock == 0)
	{
		m_fElapsedSeconds = 0.0f;
	}
	else
	{
		// convert ticks to seconds
		m_fElapsedSeconds = (float)(m_dTimerRateToSeconds * (double)ticks);
	}
}

float Timer::GetElapsedSeconds() const
{
	return m_fElapsedSeconds;
}
