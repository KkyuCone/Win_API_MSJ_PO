#pragma once
#include "ActorObjBase.h"
#include "TimerCal.h"
#include <string>

class AnimationRenderer;
class SoundControl;
class InGameTimer : public ActorObjBase
{
public:
	friend MainSceneState;

private:
	AnimationRenderer* m_VictoryDefeat_First;
	AnimationRenderer* m_VictoryDefeat_Second;
	AnimationRenderer* m_VictoryDefeat_Third;
	AnimationRenderer* m_VictoryDefeat_Fourth;
	AnimationRenderer* m_VictoryDefeat_Fifth;
	AnimationRenderer* m_VictoryDefeat_Sixth;
	AnimationRenderer* m_VictoryDefeat_Seventh;

	TimerCal m_StartCal;
	bool m_StartImage;

	bool m_BalckEmtpy;

private:
	AnimationRenderer* m_ZeroRender;
	AnimationRenderer* m_FirstRender;
	AnimationRenderer* m_SecondRender;
	AnimationRenderer* m_ThirdRender;
	TimerCal m_Second;			
	TimerCal m_Timer;

	AnimationRenderer* m_GameDrawBack;
	bool m_GameDraw;


	SoundControl* m_VictoryOrDefeatSound;

	std::wstring m_ThirdChangeName;
	std::wstring m_SecondChangeName;
	std::wstring m_FirstChangeName;

	int Third_Count;
	int Second_Count;
	int First_Count;

	bool First_Zero;
	bool Second_Zero;
	bool GameOver;


public:
	InGameTimer();
	~InGameTimer();


public:
	void Start_Update() override;
	void Prev_Update() override;
	void Update() override;
	void Late_Update() override;
	void DebugRender() override;

public:
	void Timer();
	std::wstring ImageCount(int _Count);
	void Timer_ImageChange(AnimationRenderer* _ChangeRender, std::wstring _ChangeAniName);

	void GameDraw_Init();
	void GameDraw_Update();

	void BlackEmtpy_Init();
	void BlackEmtpy_Update();

	void BalckEmtpyValueChange(bool _Value);

	bool Get_m_BalckEmtpy()
	{
		return m_BalckEmtpy;
	}

public:
	// È¿°úÀ½
	void Sound_Draw();
	void Sound_Win();
	void Sound_Lose();
	void Sound_Start();
};

