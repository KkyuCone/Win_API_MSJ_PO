#include "stdafx.h"
#include "Monster.h"
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

/////////////////////////////////////////////////////////////////

Monster::Monster()
	: m_Rectange{ { 0.0f, 0.0f },{ 100.0f, 100.0f } }
	, m_SpriteSize(0), m_BombTimer(5.0f), m_DeathTimer(1.5f),
	m_MonsterState(MONSTER_STATE::IDLE), m_bIsBubble(false), m_bDeath(false),
	pObjCol(nullptr), m_MonsterSpeed(120.0f), m_WaitIdleTime(2.0f), m_bChangeIdle(false),
	m_AttackTime(3.0f), m_bAttack(false), m_RunToChangeTime(5.0f), m_Shot(false), m_ShotTimer(2.0f),
	m_MonsterBubble(false), m_Death(false), m_BubbleSecondTimer(3.0f),
	MoveEnable(false), MoveEnableTime(2.0f)
{
	m_MonsterHP = 50;

	MonsterPosInit();
}


Monster::~Monster()
{
}

/////////////////////////////////////////////////////////////////

void Monster::MonsterPosInit()
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
		m_BasePos = { 400.0f, 400.0f };				// Vilage_00
	}
	else if (L"Vilage_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 220.0f, 550.0f };				// Vilage_01
	}
}

void Monster::Start_Update()
{
	RandomAttackValue();

	AnimName[IDLE] = L"Idle";
	AnimName[RUN] = L"Run";
	AnimName[ATTACK] = L"Attack";
	AnimName[DAMAGE] = L"Damage";
	AnimName[Death_01] = L"Death_01";
	AnimName[Death_02] = L"Death_02";
	AnimName[Death_03] = L"Death_03";
	AnimName[Death_End] = L"Death_End";
	AnimName[BubblePop] = L"Idle";


	Direction = L"D";

	// 충돌
	pObjCol = Create_Collision(L"Monster", COL_CIRCLE);
	pObjCol->Name = L"Monster";
	pObjCol->Pivot(F_Position(3, 45));
	pObjCol->Size(F_Position(60.0f, 60.0f));

	p_MonsterUpCol = Create_Collision(L"Monster_Up");
	p_MonsterUpCol->Name = L"Monster_Up";
	p_MonsterUpCol->Pivot(F_Position(2, 10));
	p_MonsterUpCol->Size(F_Position(10, 10));

	p_MonsterDownCol = Create_Collision(L"Monster_Down");
	p_MonsterDownCol->Name = L"Monster_Down";
	p_MonsterDownCol->Pivot(F_Position(2, 80));
	p_MonsterDownCol->Size(F_Position(10, 10));

	p_MonsterLeftCol = Create_Collision(L"Monster_Left");
	p_MonsterLeftCol->Name = L"Monster_Left";
	p_MonsterLeftCol->Pivot(F_Position(-35.0f, 45));
	p_MonsterLeftCol->Size(F_Position(10, 10));

	p_MonsterRightCol = Create_Collision(L"Monster_Right");
	p_MonsterRightCol->Name = L"Monster_Right";
	p_MonsterRightCol->Pivot(F_Position(38.0f, 45));
	p_MonsterRightCol->Size(F_Position(10, 10));

	// 그림자 렌더
	AnimationRenderer* m_MonsterShadowRender;
	m_MonsterShadowRender = Create_Renderer<AnimationRenderer>(11);
	m_MonsterShadowRender->Set_Alpha(150);
	m_MonsterShadowRender->Pivot(F_Position{ 0,-15 });
	m_MonsterShadowRender->Size(F_Position{ 200, 200 });
	m_MonsterShadowRender->Animation_Create(L"ItemShadow", L"PlayerShadow.bmp", 0, 0, true);
	m_MonsterShadowRender->Animation_Change(L"ItemShadow");


	// 렌더
	m_pTestAniRenderer = Create_Renderer<AnimationRenderer>(11);
	m_pTestAniRenderer->Size(F_Position{ 150, 150 });


	m_pTestAniRenderer->Animation_Create(L"Att", L"unit_bazzi.bmp", 3, 10, false, 0.15f);

	m_pTestAniRenderer->Animation_Create(L"UIdle", L"Monster_06.bmp", 0, 0, true);
	m_pTestAniRenderer->Animation_Create(L"URun", L"Monster_06.bmp", 0, 2, true, 0.25f);
	m_pTestAniRenderer->Animation_Create(L"UAttack", L"Monster_06.bmp", 24, 27, true, 0.1f);

	m_pTestAniRenderer->Animation_Create(L"DIdle", L"Monster_06.bmp", 2, 2, true);
	m_pTestAniRenderer->Animation_Create(L"DRun", L"Monster_06.bmp", 2, 4, true, 0.25f);
	m_pTestAniRenderer->Animation_Create(L"DAttack", L"Monster_06.bmp", 24, 27, true, 0.1f);

	m_pTestAniRenderer->Animation_Create(L"RIdle", L"Monster_06.bmp", 8, 8, true);
	m_pTestAniRenderer->Animation_Create(L"RRun", L"Monster_06.bmp", 8, 10, true, 0.25f);
	m_pTestAniRenderer->Animation_Create(L"RAttack", L"Monster_06.bmp", 24, 27, true, 0.1f);

	m_pTestAniRenderer->Animation_Create(L"LIdle", L"Monster_06.bmp", 6, 6, true);
	m_pTestAniRenderer->Animation_Create(L"LRun", L"Monster_06.bmp", 6, 8, true, 0.25f);
	m_pTestAniRenderer->Animation_Create(L"LAttack", L"Monster_06.bmp", 24, 27, true, 0.1f);

	m_pTestAniRenderer->Animation_Create(L"UDamage", L"Monster_06.bmp", 30, 32, true, 0.1f);
	m_pTestAniRenderer->Animation_Create(L"DDamage", L"Monster_06.bmp", 33, 35, true, 0.1f);
	m_pTestAniRenderer->Animation_Create(L"LDamage", L"Monster_06.bmp", 36, 38, true, 0.1f);
	m_pTestAniRenderer->Animation_Create(L"RDamage", L"Monster_06.bmp", 39, 41, true, 0.1f);

	// 물풍선되기1
	m_pTestAniRenderer->Animation_Create(L"Death_01", L"Monster_06.bmp", 12, 16, false, 0.2f);

	// 물풍선되기2 (반복구간)
	m_pTestAniRenderer->Animation_Create(L"Death_02", L"Monster_06.bmp", 14, 16, true, 0.15f);

	// 물풍선되기3 (사망구간)
	m_pTestAniRenderer->Animation_Create(L"Death_03", L"Monster_06.bmp", 14, 18, false, 0.2f);

	// 사망
	m_pTestAniRenderer->Animation_Create(L"Death_End", L"Monster_06.bmp", 18, 22, false, 0.1f);

	m_pTestAniRenderer->Animation_Create(L"Death_Effect", L"Monster_06.bmp", 23, 23, false, 0.1f);

	m_pTestAniRenderer->Animation_Change(L"DRun");


	// 몬스터 상태
	m_MonsterState = RUN;
	m_HPBar.Init(this, &m_MonsterHP, 500, F_Position{ 80, 10 });
}

void Monster::Prev_Update()
{
}

float AniTime = 0.0f;

void Monster::Update()
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

	if (true == InputManager::Instance().Down(L"MonsterAttack"))
	{
		BubbleAttack(3, pObjCol->ParentPos());
		Monster_ChangeState(TEST);
	}

	switch (m_MonsterState)
	{
	case Monster::IDLE:
		Idle();
		break;
	case Monster::RUN:
		Run();
		break;
	case Monster::ATTACK:
		Attack();
		break;
	case Monster::DAMAGE:
		Damage();
		break;
	case Monster::Death_01:
		Bubble_First();
		break;
	case Monster::Death_02:
		Bubble_Second();
		break;
	case Monster::Death_03:
		Bubble_Third();
		break;
	case Monster::Death_End:
		Death();
		break;
	case Monster::BubblePop:
		break;
	case Monster::TEST:
		Test();
		break;
	default:
		break;
	}
}

void Monster::Late_Update()
{
}

// 충돌
void Monster::Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other)
{
	if (_Other->Name == L"Bomb")
	{
		// 물풍선 되기
		if (true == m_HPBar.Death())
		{
			Monster_ChangeState(Death_01);
			//if (m_MonsterBubble == true)
			//	return;

			//if (true == m_pTestAniRenderer->IsCurAnimation(L"Death_01"))
			//	return;

			//m_pTestAniRenderer->Animation_Change(L"Death_01");
			//m_MonsterBubble = true;
		}
		else
		{
			// 찌릿찌릿
			Monster_ChangeState(DAMAGE);
		}

	}

	if (_This->Name == L"Monster" && _Other->Name == L"Player")
	{
		if (true == m_MonsterBubble && false == m_Death)
		{
			Monster_ChangeState(Death_End);
			m_Death = true;
			m_MonsterBubble = false;

			return;
		}
	}

}

void Monster::Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other)
{

}

void Monster::Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other)
{

}

// 위치를 타일 인덱스로 바꾸기
void Monster::Pos_Init()
{
	F_Position CharPos = m_TileRenderer->OriginTilePos(m_BasePos);
	m_BasePos = CharPos;
}


std::wstring Monster::DirectionCheck()
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

	

	/*if (CheckDir != Direction)
	{
		if (true == m_bDeath)
		{
			return;
		}

		std::wstring Ani_Name = CheckDir + AnimName[m_MonsterState];
		m_pTestAniRenderer->Animation_Change(Ani_Name.c_str());
		Direction = CheckDir;
	}*/
}

bool Monster::CanMove(std::wstring _Dir)
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
void Monster::RandomDirection()
{

}

void Monster::Move()
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
void Monster::Monster_ChangeState(MONSTER_STATE _State)
{
	m_MonsterState = _State;
}


void Monster::RandomAttackValue()
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



// 몬스터 물줄기 공격
void Monster::BubbleAttack(int _Value, F_Position _MonsterPos)		// (몬스터와 떨어질 거리(인덱스), 몬스터의 위치)
{
	if (1 >= _Value)
	{
		return;			// 공격하지 않음
	}

	int OriginPluse = _Value;
	int OriginMinus = -(_Value);

	F_Position MonsterPos = _MonsterPos;
	F_Position BubblePos = F_Position{ 0,0 };
	VECTOR2_INT  MonsterIndex = m_TileRenderer->OriginTileIndex(MonsterPos);			// 몬스터의 인덱스
	VECTOR2_INT MonsterBubbleIndex;
	int TileObjValue = -2;																// 타일 오브젝트가 있는지 판단하려고 사용

	// 상
	for (int x = OriginMinus; x <= OriginPluse; x++)
	{
		MonsterBubbleIndex = (VECTOR2_INT(MonsterIndex) + VECTOR2_INT(x, OriginMinus));
		std::set<__int64>::iterator Find_Index = m_BubbleIndex.find(MonsterBubbleIndex);
		TileObjValue = m_TileRenderer->Get_TileObjData(MonsterBubbleIndex);

		if (TileObjValue != -1)
		{
			continue;
		}

		if (Find_Index == m_BubbleIndex.end())
		{
			m_BubbleIndex.insert(std::set<__int64>::value_type(MonsterBubbleIndex));			// 해당 자리에 물줄기가 없다면, 물줄기생성
			BubblePos = m_TileRenderer->OriginTilePos(MonsterBubbleIndex);

			// 블럭이 없을때만 물줄기 생성
			if (-1 == TileObjValue)
			{
				Bubble* pNewBubble = Stage()->Create_Actor<Bubble>();
				pNewBubble->Set_BubbleCount(1);
				pNewBubble->m_TileMap = m_TileMap;
				pNewBubble->m_TileRenderer = m_TileRenderer;
				pNewBubble->Pos(BubblePos);
				pNewBubble->Set_BubbleIndex(MonsterBubbleIndex);
				pNewBubble->Set_Monster(this);
			}
		}
	}

	// 하
	for (int x = OriginMinus; x <= OriginPluse; x++)
	{
		MonsterBubbleIndex = (VECTOR2_INT(MonsterIndex) + VECTOR2_INT(x, OriginPluse));
		std::set<__int64>::iterator Find_Index = m_BubbleIndex.find(MonsterBubbleIndex);
		TileObjValue = m_TileRenderer->Get_TileObjData(MonsterBubbleIndex);

		if (TileObjValue != -1)
		{
			continue;
		}

		if (Find_Index == m_BubbleIndex.end())
		{
			m_BubbleIndex.insert(std::set<__int64>::value_type(MonsterBubbleIndex));			// 해당 자리에 물줄기가 없다면, 물줄기생성
			BubblePos = m_TileRenderer->OriginTilePos(MonsterBubbleIndex);

			//// 블럭이 없을때만 물줄기 생성
			if (-1 == TileObjValue)
			{
				Bubble* pNewBubble = Stage()->Create_Actor<Bubble>();
				pNewBubble->Set_BubbleCount(1);
				pNewBubble->m_TileMap = m_TileMap;
				pNewBubble->m_TileRenderer = m_TileRenderer;
				pNewBubble->Pos(BubblePos);
				pNewBubble->Set_BubbleIndex(MonsterBubbleIndex);
				pNewBubble->Set_Monster(this);
			}
		}
	}

	// 좌
	for (int y = OriginMinus; y <= OriginPluse; y++)
	{
		MonsterBubbleIndex = (VECTOR2_INT(MonsterIndex) + VECTOR2_INT(OriginMinus, y));
		std::set<__int64>::iterator Find_Index = m_BubbleIndex.find(MonsterBubbleIndex);
		TileObjValue = m_TileRenderer->Get_TileObjData(MonsterBubbleIndex);

		if (TileObjValue != -1)
		{
			continue;
		}

		int a = 0;

		if (Find_Index == m_BubbleIndex.end())
		{
			m_BubbleIndex.insert(std::set<__int64>::value_type(MonsterBubbleIndex));			// 해당 자리에 물줄기가 없다면, 물줄기생성
			BubblePos = m_TileRenderer->OriginTilePos(MonsterBubbleIndex);

			//// 블럭이 없을때만 물줄기 생성
			if (-1 == TileObjValue)
			{
				Bubble* pNewBubble = Stage()->Create_Actor<Bubble>();
				pNewBubble->Set_BubbleCount(1);
				pNewBubble->m_TileMap = m_TileMap;
				pNewBubble->m_TileRenderer = m_TileRenderer;
				pNewBubble->Pos(BubblePos);
				pNewBubble->Set_BubbleIndex(MonsterBubbleIndex);
				pNewBubble->Set_Monster(this);
			}
		}
	}

	// 우
	for (int y = OriginMinus; y <= OriginPluse; y++)
	{
		MonsterBubbleIndex = (VECTOR2_INT(MonsterIndex) + VECTOR2_INT(OriginPluse, y));
		std::set<__int64>::iterator Find_Index = m_BubbleIndex.find(MonsterBubbleIndex);
		TileObjValue = m_TileRenderer->Get_TileObjData(MonsterBubbleIndex);

		if (TileObjValue != -1)
		{
			continue;
		}

		int a = 0;

		if (Find_Index == m_BubbleIndex.end())
		{
			m_BubbleIndex.insert(std::set<__int64>::value_type(MonsterBubbleIndex));			// 해당 자리에 물줄기가 없다면, 물줄기생성
			BubblePos = m_TileRenderer->OriginTilePos(MonsterBubbleIndex);

			//// 블럭이 없을때만 물줄기 생성
			if (-1 == TileObjValue)
			{
				Bubble* pNewBubble = Stage()->Create_Actor<Bubble>();
				pNewBubble->Set_BubbleCount(1);
				pNewBubble->m_TileMap = m_TileMap;
				pNewBubble->m_TileRenderer = m_TileRenderer;
				pNewBubble->Pos(BubblePos);
				pNewBubble->Set_BubbleIndex(MonsterBubbleIndex);
				pNewBubble->Set_Monster(this);
			}
		}
	}



	if (m_BubbleIndex.size() >= 1)
	{
		m_BubbleIndex.clear();
	}
}





