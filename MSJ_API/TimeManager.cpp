#include "stdafx.h"
#include "TimeManager.h"

///////////////////////////////////////// Timer
TimeManager::Timer::Timer()
	: Count(), Current_Time(), Previous_Time(), deltaTime(0.0f)
	, m_ElapseTime(0.0f), m_FPSCount(0), m_FPS(0)
{
	QueryPerformanceFrequency(&Count);
	QueryPerformanceCounter(&Current_Time);

	Previous_Time = Current_Time;
}

TimeManager::Timer::~Timer()
{
}

void TimeManager::Timer::Timer_Update()
{
	float a = deltaTime;
	QueryPerformanceCounter(&Current_Time);
	deltaTime = (Current_Time.QuadPart - Previous_Time.QuadPart) / (float)Count.QuadPart;
	Previous_Time = Current_Time;
}

void TimeManager::Timer::Timer_FPS()
{
	++m_FPSCount;
	m_ElapseTime += deltaTime;

	if (m_ElapseTime >= 1.0f)
	{
		m_FPS = m_FPSCount;
		m_FPSCount = 0;
		m_ElapseTime = 0.0f;
	}
}


///////////////////////////////////////// TimeManager
TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}

void TimeManager::TimeManager_Update()
{
	m_Timer.Timer_Update();
	m_Timer.Timer_FPS();
}

