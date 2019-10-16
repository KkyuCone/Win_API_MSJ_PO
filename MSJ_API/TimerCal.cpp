#include "stdafx.h"
#include "TimerCal.h"
#include "TimeManager.h"

///////////////////////////////////////////////

TimerCal::TimerCal(float _Time) :  m_EndTime(_Time), m_CurTime(0.0f)
{
}


TimerCal::~TimerCal()
{
}

///////////////////////////////////////////////

void TimerCal::TimerReset()
{
	m_CurTime = 0.0f;
}

bool TimerCal::TimerCheck()
{
	m_CurTime += TimeManager::Instance().DeltaTime();

	if (m_CurTime >= m_EndTime)
	{
		return true;
	}

	return false;
}


void TimerCal::TimerEnd()
{
	m_CurTime = m_EndTime;
}