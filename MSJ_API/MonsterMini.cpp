#include "stdafx.h"
#include "MonsterMini.h"
#include "Util_Core.h"
#include "MainSceneState.h"
#include "SingleRenderer.h"
#include "AnimationRenderer.h"
#include "ResourceManager.h"
#include "ObjectCollision.h"
#include <cstdlib>
#include <ctime>
#include "HPBar.h"
#include "Bubble.h"
#include "InGameTimer.h"


MonsterMini::MonsterMini()
	: m_Rectange{ { 0.0f, 0.0f },{ 100.0f, 100.0f } }
	, m_SpriteSize(0), m_BombTimer(5.0f), m_DeathTimer(1.5f),
	m_MonsterState(MINIMONSTER_STATE::IDLE), m_bIsBubble(false), m_bDeath(false),
	pObjCol(nullptr), m_MonsterSpeed(120.0f), m_WaitIdleTime(2.0f), m_bChangeIdle(false),
	m_AttackTime(3.0f), m_bAttack(false), m_RunToChangeTime(5.0f), m_Shot(false), m_ShotTimer(2.0f),
	m_MonsterBubble(false), m_Death(false), m_BubbleSecondTimer(3.0f),
	MoveEnable(false), MoveEnableTime(2.0f)
{
	MonsterPosInit();
}


MonsterMini::~MonsterMini()
{
}


//

void MonsterMini::MonsterPosInit()
{

	// 맵에 따른 몬스터 초기 위치설정
	if (L"Cookie_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 389, 473 };
	}
	else if (L"Cookie_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 389, 473 };
	}
	else if (L"Desert_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 434, 378 };
	}
	else if (L"Desert_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 503, 474 };
	}
	else if (L"Forest_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 401, 484 };
	}
	else if (L"Forest_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 430, 632 };
	}
	else if (L"Ice_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 724, 493 };
	}
	else if (L"Ice_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 303, 580 };
	}
	else if (L"Pirate_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 440, 555 };
	}
	else if (L"Pirate_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 410, 621 };
	}
	else if (L"Vilage_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 63.0f, 655.0f };				// Vilage_00
	}
	else if (L"Vilage_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 220.0f, 550.0f };				// Vilage_01
	}
}

void MonsterMini::Start_Update()
{
	RandomAttackValue();

	AnimName[IDLE] = L"Idle";
	AnimName[RUN] = L"Run";
	AnimName[DAMAGE] = L"Damage";
	AnimName[Death_01] = L"Death_01";
	AnimName[Death_02] = L"Death_02";
	AnimName[Death_03] = L"Death_03";
	AnimName[Death_End] = L"Death_End";
	AnimName[BubblePop] = L"Idle";


	Direction = L"D";

	// 충돌
	pObjCol = Create_Collision(L"MiniMonster", COL_CIRCLE);
	pObjCol->Name = L"MiniMonster";
	pObjCol->Pivot(F_Position(0, 30));
	pObjCol->Size(F_Position(30.0f, 30.0f));

	p_MonsterUpCol = Create_Collision(L"Monster_Up");
	p_MonsterUpCol->Name = L"Monster_Up";
	p_MonsterUpCol->Pivot(F_Position(2, 5));
	p_MonsterUpCol->Size(F_Position(10, 10));

	p_MonsterDownCol = Create_Collision(L"Monster_Down");
	p_MonsterDownCol->Name = L"Monster_Down";
	p_MonsterDownCol->Pivot(F_Position(2, 50));
	p_MonsterDownCol->Size(F_Position(10, 10));

	p_MonsterLeftCol = Create_Collision(L"Monster_Left");
	p_MonsterLeftCol->Name = L"Monster_Left";
	p_MonsterLeftCol->Pivot(F_Position(-25.0f, 30));
	p_MonsterLeftCol->Size(F_Position(10, 10));

	p_MonsterRightCol = Create_Collision(L"Monster_Right");
	p_MonsterRightCol->Name = L"Monster_Right";
	p_MonsterRightCol->Pivot(F_Position(28.0f, 30));
	p_MonsterRightCol->Size(F_Position(10, 10));

	// 그림자 렌더
	AnimationRenderer* m_MonsterShadowRender;
	m_MonsterShadowRender = Create_Renderer<AnimationRenderer>(11);
	m_MonsterShadowRender->Set_Alpha(150);
	m_MonsterShadowRender->Pivot(F_Position{ 0,-15 });
	m_MonsterShadowRender->Size(F_Position{ 100, 100 });
	m_MonsterShadowRender->Animation_Create(L"ItemShadow", L"PlayerShadow.bmp", 0, 0, true);
	m_MonsterShadowRender->Animation_Change(L"ItemShadow");


	// 렌더
	m_pTestAniRenderer = Create_Renderer<AnimationRenderer>(11);
	m_pTestAniRenderer->Size(F_Position{ 100, 100 });

	m_pTestAniRenderer->Animation_Create(L"UIdle", L"Monster_01.bmp", 0, 0, true);
	m_pTestAniRenderer->Animation_Create(L"URun", L"Monster_01.bmp", 0, 2, true, 0.25f);

	m_pTestAniRenderer->Animation_Create(L"DIdle", L"Monster_01.bmp", 2, 2, true);
	m_pTestAniRenderer->Animation_Create(L"DRun", L"Monster_01.bmp", 5, 7, true, 0.25f);

	m_pTestAniRenderer->Animation_Create(L"RIdle", L"Monster_01.bmp", 8, 8, true);
	m_pTestAniRenderer->Animation_Create(L"RRun", L"Monster_01.bmp", 15, 17, true, 0.25f);

	m_pTestAniRenderer->Animation_Create(L"LIdle", L"Monster_01.bmp", 6, 6, true);
	m_pTestAniRenderer->Animation_Create(L"LRun", L"Monster_01.bmp", 10, 12, true, 0.25f);

	m_pTestAniRenderer->Animation_Create(L"UDamage", L"Monster_01.bmp", 20, 23, true);
	m_pTestAniRenderer->Animation_Create(L"DDamage", L"Monster_01.bmp", 20, 23, true);
	m_pTestAniRenderer->Animation_Create(L"LDamage", L"Monster_01.bmp", 20, 23, true);
	m_pTestAniRenderer->Animation_Create(L"RDamage", L"Monster_01.bmp", 20, 23, true);

	// 사망
	m_pTestAniRenderer->Animation_Create(L"Death_01", L"Monster_01.bmp", 12, 16, false, 0.2f);


	m_pTestAniRenderer->Animation_Create(L"Death_Effect", L"Monster_01.bmp", 23, 23, false, 0.1f);

	m_pTestAniRenderer->Animation_Change(L"DRun");


	// 몬스터 상태
	m_MonsterState = RUN;
}

void MonsterMini::Prev_Update()
{
}


void MonsterMini::Update()
{

	if (false == MoveEnable)
	{
		if (true == MoveEnableTime.TimerCheck())
		{
			MoveEnable = true;
			MoveEnableTime.TimerReset();
		}
		return;
	}

	switch (m_MonsterState)
	{
	case MonsterMini::IDLE:
		Idle();
		break;
	case MonsterMini::RUN:
		Run();
		break;
	case MonsterMini::DAMAGE:
		Damage();
		break;
	case MonsterMini::Death_01:
		Bubble_First();
		break;
	default:
		break;
	}
}

void MonsterMini::Late_Update()
{
}

// 충돌
void MonsterMini::Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other)
{
	if (_Other->Name == L"Bomb")
	{
		// 데스
		Monster_ChangeState(Death_01);
	}
}

void MonsterMini::Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other)
{

}

void MonsterMini::Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other)
{

}

// 위치를 타일 인덱스로 바꾸기
void MonsterMini::Pos_Init()
{
	F_Position CharPos = m_TileRenderer->OriginTilePos(m_BasePos);
	m_BasePos = CharPos;
}


std::wstring MonsterMini::DirectionCheck()
{
	std::wstring CheckDir = Direction;
	bool EnableDirMove = CanMove(CheckDir);
	int DirValue = 0;

	if (true == EnableDirMove)
		return CheckDir;

	if (CheckDir == L"U")
	{
		DirValue = 0;
	}
	else if (CheckDir == L"D")
	{
		DirValue = 1;
	}
	else if (CheckDir == L"R")
	{
		DirValue = 3;
	}
	else if (CheckDir == L"L")
	{
		DirValue = 2;
	}

	while (true)
	{
		// 시드값으로 현재 시간(초)를 입력

		int DirRandom = rand() % 4;

		if (DirRandom == DirValue)
		{
			continue;
		}

		switch (DirRandom)
		{
		case 0:
			CheckDir = L"U";
			break;
		case 1:
			CheckDir = L"D";
			break;
		case 2:
			CheckDir = L"L";
			break;
		case 3:
			CheckDir = L"R";
			break;
		default:
			CheckDir = L"";
			break;
		}

		// 해당 타일 인덱스로 갈수 있는지 체크하기
		EnableDirMove = CanMove(CheckDir);			// false면 다시 체크 true면 나가기

		if (true == EnableDirMove)
		{
			break;
		}

	}


	if (CheckDir != Direction)
	{
		if (true == m_bDeath)
		{
			return L"";
		}

		std::wstring Ani_Name = CheckDir + AnimName[m_MonsterState];
		m_pTestAniRenderer->Animation_Change(Ani_Name.c_str());
		Direction = CheckDir;
	}


	return CheckDir;
}

bool MonsterMini::CanMove(std::wstring _Dir)
{
	F_Position Pos = { 0,0 };
	VECTOR2_INT Index = { -1, -1 };
	bool EnablePos = false;

	if (_Dir == L"L")
	{
		Pos = p_MonsterLeftCol->ParentPos();
	}
	else if (_Dir == L"R")
	{
		Pos = p_MonsterRightCol->ParentPos();
	}
	else if (_Dir == L"U")
	{
		Pos = p_MonsterUpCol->ParentPos();
	}
	else if (_Dir == L"D")
	{
		Pos = p_MonsterDownCol->ParentPos();
	}
	else
	{
		return false;
	}

	Index = m_TileRenderer->OriginTileIndex(Pos);

	int TileData = m_TileRenderer->Get_TileObjData(Index);			// -1만 이동할 수 있음

	if (-1 != TileData)
	{
		return false;		// 해당 타일이 존재 하지 않다면 or 갈수 없는 타일이라면
	}

	return true;
}

// 막다른 길에 있을경우 갈 수 있는 방향을 체크할 함수
void MonsterMini::RandomDirection()
{

}

void MonsterMini::Move()
{
	// 방향체크

	Direction = DirectionCheck();

	if (Direction == L"")
	{
		return;
	}


	//// 움직임
	if (Direction == L"L")
	{
		m_BasePos += F_Position::LEFT * TimeManager::Instance().DeltaTime() * m_MonsterSpeed;
	}

	else if (Direction == L"R")
	{
		m_BasePos += F_Position::RIGHT * TimeManager::Instance().DeltaTime() * m_MonsterSpeed;
	}
	else if (Direction == L"U")
	{
		m_BasePos += F_Position::UP * TimeManager::Instance().DeltaTime() * m_MonsterSpeed;
	}
	else if (Direction == L"D")
	{
		m_BasePos += F_Position::DOWN * TimeManager::Instance().DeltaTime() * m_MonsterSpeed;
	}
}

// 상태 전환
void MonsterMini::Monster_ChangeState(MINIMONSTER_STATE _State)
{
	m_MonsterState = _State;
}


void MonsterMini::RandomAttackValue()
{
	int RandomValue = rand() % 100;

	if (RandomValue < 100)
	{
		m_bAttack = true;
	}
	else
	{
		m_bAttack = false;
	}
}

