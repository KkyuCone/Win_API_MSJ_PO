#include "stdafx.h"
#include "Bubble.h"
#include "ResourceManager.h"
#include "AnimationRenderer.h"
#include "ObjectCollision.h"
#include "MainSceneState.h"
#include "Player.h"


Bubble::Bubble() 
	: m_BombTimer(2.0f), m_FadeTimer(0.6f), m_bBomb(false), m_BubblePower(1), pObjCol(nullptr)
	, m_pPlayer(nullptr), m_pMonster(nullptr), m_bMonster(false),
	m_BubbleUpIndex(0,0), m_BubbleDownIndex(0,0), m_BubbleLeftIndex(0,0), m_BubbleRightIndex(0,0),
	BubbleUpValue(-1), BubbleDownValue(-1), BubbleLeftValue(-1), BubbleRightValue(-1),
	m_BubbleType(Base_Bubble)
{
	m_BubbleScale = 1.0f;
	m_BubbleState = IDLE;
}


Bubble::~Bubble()
{
}

//////////////////////////////////

void Bubble::Start_Update()
{
	// 사운드
	m_SoundControl = ResourceManager::Instance().SoundControl_Insert();

	m_BubbleSize = F_Position{ 52, 52 };
	//m_BubbleSize = F_Position{ 70, 70 };

	// 충돌
	pObjCol = Create_Collision(L"Bubble");
	pObjCol->Size(F_Position(52, 52));
	pObjCol->Name = L"Bubble";

	// 렌더

	m_pTestAniRenderer = Create_Renderer<AnimationRenderer>(9);
	m_pTestAniRenderer->Size(m_BubbleSize);
	m_pTestAniRenderer->Animation_Create(L"Bubble", L"bomb_0.bmp", 0, 3, true, 0.2f);

	m_pTestAniRenderer->Animation_Create(L"Bubble_Empty", L"bombwater_work.bmp", 3, 5, false);

	m_pTestAniRenderer->Animation_Create(L"Bomb_Mid", L"bombwater_work.bmp", 0, 2, true, 0.05f);
	m_pTestAniRenderer->Animation_Create(L"Bomb_Left", L"bombwater_work.bmp", 190, 192, true, 0.05f);
	m_pTestAniRenderer->Animation_Create(L"Bomb_Top", L"bombwater_work.bmp", 193, 195, true, 0.05f);
	m_pTestAniRenderer->Animation_Create(L"Bomb_Right", L"bombwater_work.bmp", 196, 198, true, 0.05f);
	m_pTestAniRenderer->Animation_Create(L"Bomb_Down", L"bombwater_work.bmp", 199, 201, true, 0.05f);

	m_pTestAniRenderer->Animation_Create(L"Fade_Left", L"bombwater_work.bmp", 38, 50, false, 0.05f);
	m_pTestAniRenderer->Animation_Create(L"Fade_Top", L"bombwater_work.bmp", 76, 88, false, 0.05f);
	m_pTestAniRenderer->Animation_Create(L"Fade_Right", L"bombwater_work.bmp", 114, 126, false, 0.05f);
	m_pTestAniRenderer->Animation_Create(L"Fade_Down", L"bombwater_work.bmp", 152, 164, false, 0.05f);

	m_pTestAniRenderer->Animation_Change(L"Bubble");


}

void Bubble::Prev_Update()
{

}

void Bubble::Update()
{
	ScaleRatio(m_BubbleScale);
	int a = 0;

	switch (m_BubbleState)
	{
	case Bubble::IDLE:
		Idle();
		break;
	case Bubble::BOMB:
		Bomb();
		break;
	case Bubble::FADE:
		Fade();
		break;
	case Bubble::DEATH:
		if (true == m_bMonster)
		{

		}
		else
		{
			m_pPlayer->Erase_BubbleMap(m_BubbleIndex);
		}
		Bubble_Death();
	case Bubble::OTHER:
		break;
	default:
		break;
	}

}

void Bubble::Late_Update()
{

}

void Bubble::Bubble_ChangeState(wchar_t* _pStateName)
{
	m_pTestAniRenderer->Animation_Change(_pStateName);
}


void Bubble::Set_BubbleCount(int _Count)
{
	m_BubblePower = _Count;
}

void Bubble::Set_Player(Player* _Player)
{
	m_pPlayer = _Player;
}

void Bubble::Set_Monster(Monster* _Monster)
{
	m_pMonster = _Monster;
	m_bMonster = true;
}

void Bubble::Set_BubbleIndex(VECTOR2_INT _Index)
{
	m_BubbleIndex = _Index;
}

void Bubble::BubbleState_Change()
{

}

void Bubble::Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other)
{
	if (_This == _Other)
	{
		return;
	}

	if (_This != _Other && L"Bomb" == _Other->Name && L"Bubble" == _This->Name)
	{
		int a = 0;
		m_BombTimer.TimerEnd();
	}
}

void Bubble::Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other)
{

}

void Bubble::Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other)
{

}


void Bubble::ChangeColName(std::wstring _Name)
{
	pObjCol->Name = _Name;
}

void Bubble::BubbleType_Init(int a)
{
	m_BubbleType = (BubbleType)a;
}

void Bubble::Bubble_Init(BubbleType _Type)
{
	switch (_Type)
	{
	case Bubble::Base_Bubble:
		break;
	case Bubble::Player_Bubble:
		m_pTestAniRenderer->Size(m_BubbleSize);
		m_pTestAniRenderer->Animation_Create(L"Bubble", L"bubble_127.bmp", 0, 7, true, 0.2f);

		m_pTestAniRenderer->Animation_Change(L"Bubble");
		break;
	case Bubble::Monster_Bubble:
		m_pTestAniRenderer = Create_Renderer<AnimationRenderer>(9);
		m_pTestAniRenderer->Size(m_BubbleSize);
		m_pTestAniRenderer->Animation_Create(L"Bubble", L"bubble_115.bmp", 0, 3, true, 0.2f);

		m_pTestAniRenderer->Animation_Change(L"Bubble");
		break;
	default:
		break;
	}
}
