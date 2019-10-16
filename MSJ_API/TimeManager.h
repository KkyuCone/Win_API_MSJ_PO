#pragma once

class Util_Core;
class TimeManager
{
public:
	friend Util_Core;

public:
	static TimeManager& Instance()
	{
		static TimeManager instance = TimeManager();
		return instance;
	}

private:
	class Timer
	{
	public:
		friend TimeManager;

	private:
		LARGE_INTEGER Count;
		LARGE_INTEGER Current_Time;
		LARGE_INTEGER Previous_Time;

		float deltaTime;

		//FPS
		float m_ElapseTime;		// 경과시간
		int m_FPSCount;
		int m_FPS;

	public:
		Timer();
		~Timer();

	private:
		void Timer_Update();
		void Timer_FPS();
	};

private:
	Timer m_Timer;

public:
	inline float DeltaTime() const
	{
		return m_Timer.deltaTime;
	}

	inline int FPS() const
	{
		return m_Timer.m_FPS;
	}

public:
	void TimeManager_Update();

public:
	TimeManager();
	~TimeManager();
};

