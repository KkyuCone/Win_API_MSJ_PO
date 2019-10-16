#pragma once
class TimerCal
{
private:
	float m_EndTime;
	float m_CurTime;

public:
	bool TimerCheck();
	void TimerReset();
	void TimerEnd();
public:
	TimerCal(float _Time);
	~TimerCal();
};

