#pragma once
class Timer
{
public:
	Timer();
	virtual ~Timer();

	void Create();
	void Start();
	void Stop();

	float GetElapsedSeconds() const;

private:
	double m_dTimerRateToSeconds;
	__int64 m_iStartClock;
	__int64 m_iTickFrequency;

	float m_fElapsedSeconds;
};

