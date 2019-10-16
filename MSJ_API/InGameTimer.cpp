#include "stdafx.h"
#include "InGameTimer.h"
#include "AnimationRenderer.h"
#include "ResourceManager.h"
#include "SoundControl.h"


InGameTimer::InGameTimer() 
	: m_Second(1.0f), m_Timer(180.0f), Third_Count(9), Second_Count(5), First_Count(3), m_ThirdChangeName(L""), m_SecondChangeName(L""), m_FirstChangeName(L"")
	, First_Zero(false), Second_Zero(false), GameOver(false), m_GameDrawBack(nullptr), m_GameDraw(false), m_StartCal(1.5f), m_StartImage(true), m_BalckEmtpy(false)
{
}


InGameTimer::~InGameTimer()
{
}

//////////////////////////////////////////////

void InGameTimer::Start_Update()
{
	m_GameDrawBack = Create_Renderer<AnimationRenderer>(20);
	// 효과음
	m_VictoryOrDefeatSound = ResourceManager::Instance().SoundControl_Insert();

	// 0번째(의미없는 숫자)
	m_ZeroRender = Create_Renderer<AnimationRenderer>(15);
	m_ZeroRender->Pivot(F_Position{ 915, 103 });
	m_ZeroRender->Size(F_Position{ 22, 26 });
	m_ZeroRender->Animation_Create(L"Zero", L"Number.bmp", 10, 10, false);
	m_ZeroRender->Animation_Change(L"Zero");

	// 첫번째
	m_FirstRender = Create_Renderer<AnimationRenderer>(15);
	m_FirstRender->Pivot(F_Position{ 933, 103 });
	m_FirstRender->Size(F_Position{ 22, 26 });

	m_FirstRender->Animation_Create(L"Zero", L"Number.bmp", 10, 10, false);
	m_FirstRender->Animation_Create(L"First", L"Number.bmp", 11, 11, false);
	m_FirstRender->Animation_Create(L"Second", L"Number.bmp", 12, 12, false);
	m_FirstRender->Animation_Create(L"Third", L"Number.bmp", 13, 13, false);
	m_FirstRender->Animation_Change(L"Third");

	// 두번째
	m_SecondRender = Create_Renderer<AnimationRenderer>(15);
	m_SecondRender->Pivot(F_Position{ 963, 103 });
	m_SecondRender->Size(F_Position{ 22, 26 });

	m_SecondRender->Animation_Create(L"Zero", L"Number.bmp", 10, 10, false);
	m_SecondRender->Animation_Create(L"First", L"Number.bmp", 11, 11, false);
	m_SecondRender->Animation_Create(L"Second", L"Number.bmp", 12, 12, false);
	m_SecondRender->Animation_Create(L"Third", L"Number.bmp", 13, 13, false);
	m_SecondRender->Animation_Create(L"Fourth", L"Number.bmp", 14, 14, false);
	m_SecondRender->Animation_Create(L"Fifth", L"Number.bmp", 15, 15, false);
	m_SecondRender->Animation_Change(L"Fifth");

	// 세번째
	m_ThirdRender = Create_Renderer<AnimationRenderer>(15);
	m_ThirdRender->Pivot(F_Position{ 980, 103 });
	m_ThirdRender->Size(F_Position{ 22, 26 });

	m_ThirdRender->Animation_Create(L"Zero", L"Number.bmp", 10, 10, false);
	m_ThirdRender->Animation_Create(L"First", L"Number.bmp", 11, 11, false);
	m_ThirdRender->Animation_Create(L"Second", L"Number.bmp", 12, 12, false);
	m_ThirdRender->Animation_Create(L"Third", L"Number.bmp", 13, 13, false);
	m_ThirdRender->Animation_Create(L"Fourth", L"Number.bmp", 14, 14, false);
	m_ThirdRender->Animation_Create(L"Fifth", L"Number.bmp", 15, 15, false);
	m_ThirdRender->Animation_Create(L"Sixth", L"Number.bmp", 16, 16, false);
	m_ThirdRender->Animation_Create(L"Seventh", L"Number.bmp", 17, 17, false);
	m_ThirdRender->Animation_Create(L"Eighth", L"Number.bmp", 18, 18, false);
	m_ThirdRender->Animation_Create(L"Ninth", L"Number.bmp", 19, 19, false);
	m_ThirdRender->Animation_Change(L"Ninth");


	// 스타트
	m_VictoryDefeat_First = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_First->Pivot(F_Position{ 1024/2 - 300, 768/2 - 80 });
	m_VictoryDefeat_First->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_First->Animation_Create(L"S", L"Start.bmp", 0, 0, false);
	m_VictoryDefeat_First->Animation_Change(L"S");

	m_VictoryDefeat_Second = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Second->Pivot(F_Position{ 1024 / 2 - 200, 768 / 2 - 80});
	m_VictoryDefeat_Second->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Second->Animation_Create(L"T", L"Start.bmp", 1, 1, false);
	m_VictoryDefeat_Second->Animation_Change(L"T");

	m_VictoryDefeat_Third = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Third->Pivot(F_Position{ 1024 / 2 - 100, 768 / 2 - 80});
	m_VictoryDefeat_Third->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Third->Animation_Create(L"A", L"Start.bmp", 2, 2, false);
	m_VictoryDefeat_Third->Animation_Change(L"A");

	m_VictoryDefeat_Fourth = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Fourth->Pivot(F_Position{ 1024 / 2 , 768 / 2 - 80});
	m_VictoryDefeat_Fourth->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Fourth->Animation_Create(L"R", L"Start.bmp", 3, 3, false);
	m_VictoryDefeat_Fourth->Animation_Change(L"R");

	m_VictoryDefeat_Fifth = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Fifth->Pivot(F_Position{ 1024 / 2 + 100, 768 / 2 - 80});
	m_VictoryDefeat_Fifth->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Fifth->Animation_Create(L"T", L"Start.bmp", 4, 4, false);
	m_VictoryDefeat_Fifth->Animation_Change(L"T");

	m_VictoryDefeat_Sixth = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Sixth->Pivot(F_Position{ 1024 / 2 +200, 768 / 2 - 80});
	m_VictoryDefeat_Sixth->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Sixth->Animation_Create(L"M", L"Start.bmp", 5, 5, false);
	m_VictoryDefeat_Sixth->Animation_Change(L"M");

	m_VictoryDefeat_Seventh = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Seventh->Pivot(F_Position{ 1024 / 2 + 300, 768 / 2 - 80});
	m_VictoryDefeat_Seventh->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Seventh->Animation_Create(L"X", L"Start.bmp", 6, 6, false);
	m_VictoryDefeat_Seventh->Animation_Change(L"X");


}

void InGameTimer::Prev_Update()
{

}

void InGameTimer::Update()
{
	if (true == m_BalckEmtpy)
	{
		BlackEmtpy_Update();
	}
	else
	{
		if (true == m_StartImage)
		{
			if (true == m_StartCal.TimerCheck())
			{
				m_VictoryDefeat_First->Obj_Death();
				m_VictoryDefeat_Second->Obj_Death();
				m_VictoryDefeat_Third->Obj_Death();
				m_VictoryDefeat_Fourth->Obj_Death();
				m_VictoryDefeat_Fifth->Obj_Death();
				m_VictoryDefeat_Sixth->Obj_Death();
				m_VictoryDefeat_Seventh->Obj_Death();
				m_StartImage = false;
				m_StartCal.TimerReset();
			}
		}

		if (false == GameOver)
		{
			Timer();
		}

		if (true == m_GameDraw)
		{
			// draw
			GameDraw_Update();
		}
	}

}

void InGameTimer::BalckEmtpyValueChange(bool _Value)
{
	m_BalckEmtpy = _Value;
	GameOver = true;
	m_GameDraw = false;

	BlackEmtpy_Init();
}

void InGameTimer::Late_Update()
{

}

void InGameTimer::DebugRender()
{

}

void InGameTimer::Timer()
{	
	// 1초마다
	if (true == m_Second.TimerCheck())
	{
		--Third_Count;

		if (true == First_Zero && true == Second_Zero
			&& Third_Count <= 1)
		{
			m_ThirdChangeName = ImageCount(0);
			Timer_ImageChange(m_ThirdRender, m_ThirdChangeName);
			GameOver = true;
			GameDraw_Init();
			return;
		}

		if (Third_Count < 0)
		{
			--Second_Count;

			if (Second_Count < 0)
			{
				Second_Count = 5;
				--First_Count;
			}

			Third_Count = 9;
		}


		if (true == First_Zero && Second_Count <= 0)
		{
			Second_Zero = true;
			Second_Count = 0;
		}

		if (First_Count <= 0)
		{
			First_Count = 0;
			First_Zero = true;
		}
		

		m_ThirdChangeName = ImageCount(Third_Count);
		m_SecondChangeName = ImageCount(Second_Count);
		m_FirstChangeName = ImageCount(First_Count);
		int a = 0;

		if (m_ThirdChangeName != L"")
		{
			Timer_ImageChange(m_ThirdRender, m_ThirdChangeName);
			Timer_ImageChange(m_SecondRender, m_SecondChangeName);
			Timer_ImageChange(m_FirstRender, m_FirstChangeName);
		}

		m_Second.TimerReset();
	}
}

void InGameTimer::Timer_ImageChange(AnimationRenderer* _ChangeRender, std::wstring _ChangeAniName)
{
	const wchar_t* ChangeAniName = _ChangeAniName.c_str();
	_ChangeRender->Animation_Change(ChangeAniName);
}

std::wstring InGameTimer::ImageCount(int _Count)
{
	if (_Count == 0)
	{
		return L"Zero";
	}
	else if (_Count == 1)
	{
		return L"First";
	}
	else if (_Count == 2)
	{
		return L"Second";
	}
	else if (_Count == 3)
	{
		return L"Third";
	}
	else if (_Count == 4)
	{
		return L"Fourth";
	}
	else if (_Count == 5)
	{
		return L"Fifth";
	}
	else if (_Count == 6)
	{
		return L"Sixth";
	}
	else if (_Count == 7)
	{
		return L"Seventh";
	}
	else if (_Count == 8)
	{
		return L"Eighth";
	}
	else if (_Count == 9)
	{
		return L"Ninth";
	}
	else
	{
		return L"";
	}
}


void InGameTimer::GameDraw_Init()
{
	GameOver = true;
	m_GameDraw = true;

	m_GameDrawBack = Create_Renderer<AnimationRenderer>(20);
	m_GameDrawBack->Set_Alpha(0);
	m_GameDrawBack->Animation_Create(L"FadeIn", L"BlackFadeInOut.bmp", 0, 0, false, 0.1f);
	m_GameDrawBack->Size(F_Position{ 1024, 768 });
	m_GameDrawBack->Pivot(F_Position{ 1024 / 2, 768 / 2 });

	m_GameDrawBack->Animation_Change(L"FadeIn");

	Sound_Draw();
}

void InGameTimer::BlackEmtpy_Init()
{
	m_GameDrawBack = Create_Renderer<AnimationRenderer>(20);
	m_GameDrawBack->Set_Alpha(0);
	m_GameDrawBack->Animation_Create(L"FadeIn", L"BlackFadeInOut.bmp", 0, 0, false, 0.1f);
	m_GameDrawBack->Size(F_Position{ 1024, 768 });
	m_GameDrawBack->Pivot(F_Position{ 1024 / 2, 768 / 2 });

	m_GameDrawBack->Animation_Change(L"FadeIn");
}

void InGameTimer::GameDraw_Update()
{
	m_GameDraw = false;
	if (120 <= m_GameDrawBack->Get_Alpha())
	{

		m_GameDraw = false;
		//m_GameDrawBack->Obj_Death();
	}

	if (120 >= m_GameDrawBack->Get_Alpha())
	{
		m_GameDrawBack->Set_Alpha(m_GameDrawBack->Get_Alpha() + 2);	// 서서히 보임
	}
}

void InGameTimer::BlackEmtpy_Update()
{
	if (120 <= m_GameDrawBack->Get_Alpha())
	{
		m_GameDraw = false;
	}

	if (120 >= m_GameDrawBack->Get_Alpha())
	{
		m_GameDrawBack->Set_Alpha(m_GameDrawBack->Get_Alpha() + 2);	// 서서히 보임
	}
}

void InGameTimer::Sound_Draw()
{
	m_VictoryOrDefeatSound->Sound_NewPlayItem(L"Draw.ogg");
	m_VictoryOrDefeatSound->Sound_SetPitch(1.0f);

	m_VictoryDefeat_First = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_First->Pivot(F_Position{ 1024 / 2 - 250, 768 / 2 - 80 });
	m_VictoryDefeat_First->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_First->Animation_Create(L"D", L"Draw.bmp", 0, 0, false);
	m_VictoryDefeat_First->Animation_Change(L"D");

	m_VictoryDefeat_Second = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Second->Pivot(F_Position{ 1024 / 2 - 150, 768 / 2 - 80 });
	m_VictoryDefeat_Second->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Second->Animation_Create(L"R", L"Draw.bmp", 1, 1, false);
	m_VictoryDefeat_Second->Animation_Change(L"R");

	m_VictoryDefeat_Third = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Third->Pivot(F_Position{ 1024 / 2 - 50, 768 / 2 - 80 });
	m_VictoryDefeat_Third->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Third->Animation_Create(L"A", L"Draw.bmp", 2, 2, false);
	m_VictoryDefeat_Third->Animation_Change(L"A");

	m_VictoryDefeat_Fourth = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Fourth->Pivot(F_Position{ 1024 / 2 + 50, 768 / 2 - 80 });
	m_VictoryDefeat_Fourth->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Fourth->Animation_Create(L"W", L"Draw.bmp", 3, 3, false);
	m_VictoryDefeat_Fourth->Animation_Change(L"W");

	m_VictoryDefeat_Fifth = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Fifth->Pivot(F_Position{ 1024 / 2 + 150, 768 / 2 - 80 });
	m_VictoryDefeat_Fifth->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Fifth->Animation_Create(L"T", L"Draw.bmp", 4, 4, false);
	m_VictoryDefeat_Fifth->Animation_Change(L"T");
}

void InGameTimer::Sound_Win()
{
	m_VictoryOrDefeatSound->Sound_NewPlayItem(L"Win.ogg");
	m_VictoryOrDefeatSound->Sound_SetPitch(1.0f);

	m_VictoryDefeat_First = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_First->Pivot(F_Position{ 1024 / 2 - 250, 768 / 2 - 80 });
	m_VictoryDefeat_First->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_First->Animation_Create(L"W", L"Win.bmp", 0, 0, false);
	m_VictoryDefeat_First->Animation_Change(L"W");

	m_VictoryDefeat_Second = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Second->Pivot(F_Position{ 1024 / 2 - 150, 768 / 2 - 80 });
	m_VictoryDefeat_Second->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Second->Animation_Create(L"I", L"Win.bmp", 1, 1, false);
	m_VictoryDefeat_Second->Animation_Change(L"I");

	m_VictoryDefeat_Third = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Third->Pivot(F_Position{ 1024 / 2 - 50, 768 / 2 - 80 });
	m_VictoryDefeat_Third->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Third->Animation_Create(L"N", L"Win.bmp", 2, 2, false);
	m_VictoryDefeat_Third->Animation_Change(L"N");

	m_VictoryDefeat_Fourth = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Fourth->Pivot(F_Position{ 1024 / 2 + 50, 768 / 2 - 80 });
	m_VictoryDefeat_Fourth->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Fourth->Animation_Create(L"D", L"Win.bmp", 3, 3, false);
	m_VictoryDefeat_Fourth->Animation_Change(L"D");
}

void InGameTimer::Sound_Lose()
{
	m_VictoryOrDefeatSound->Sound_NewPlayItem(L"Lose.ogg");
	m_VictoryOrDefeatSound->Sound_SetPitch(1.0f);

	m_VictoryDefeat_First = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_First->Pivot(F_Position{ 1024 / 2 - 250, 768 / 2 - 80 });
	m_VictoryDefeat_First->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_First->Animation_Create(L"L", L"Lose.bmp", 0, 0, false);
	m_VictoryDefeat_First->Animation_Change(L"L");

	m_VictoryDefeat_Second = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Second->Pivot(F_Position{ 1024 / 2 - 150, 768 / 2 - 80 });
	m_VictoryDefeat_Second->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Second->Animation_Create(L"O", L"Lose.bmp", 1, 1, false);
	m_VictoryDefeat_Second->Animation_Change(L"O");

	m_VictoryDefeat_Third = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Third->Pivot(F_Position{ 1024 / 2 - 50, 768 / 2 - 80 });
	m_VictoryDefeat_Third->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Third->Animation_Create(L"S", L"Lose.bmp", 2, 2, false);
	m_VictoryDefeat_Third->Animation_Change(L"S");

	m_VictoryDefeat_Fourth = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Fourth->Pivot(F_Position{ 1024 / 2 + 50, 768 / 2 - 80 });
	m_VictoryDefeat_Fourth->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Fourth->Animation_Create(L"E", L"Lose.bmp", 3, 3, false);
	m_VictoryDefeat_Fourth->Animation_Change(L"E");

	m_VictoryDefeat_Fifth = Create_Renderer<AnimationRenderer>(25);
	m_VictoryDefeat_Fifth->Pivot(F_Position{ 1024 / 2 + 150, 768 / 2 - 80 });
	m_VictoryDefeat_Fifth->Size(F_Position{ 100, 100 });
	m_VictoryDefeat_Fifth->Animation_Create(L"T", L"Lose.bmp", 4, 4, false);
	m_VictoryDefeat_Fifth->Animation_Change(L"T");
}

void InGameTimer::Sound_Start()
{
	m_VictoryOrDefeatSound->Sound_NewPlayItem(L"GameStart.ogg");
	m_VictoryOrDefeatSound->Sound_SetPitch(1.0f);
}
