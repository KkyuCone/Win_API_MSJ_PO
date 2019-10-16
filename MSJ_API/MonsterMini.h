#pragma once
#include "ActorObjBase.h"
#include "TimerCal.h"
#include "TileMapRenderer.h"
#include "HPBar.h"
#include "Bubble.h"
#include <set>


class AnimationRenderer;
class SingleRenderer;
class EditorTileMap;
class InGameTimer;
class MonsterMini : public ActorObjBase
{
public:
	friend class MainSceneState;

public:
	InGameTimer* m_InGameTimer;

private:
	bool MoveEnable;
	TimerCal MoveEnableTime;


	int m_MonsterHP;
	F_Rectangle m_Rectange;
	int m_SpriteSize;
	AnimationRenderer* m_pTestAniRenderer;

	TimerCal m_BombTimer;
	TimerCal m_DeathTimer;
	TimerCal m_ShotTimer;
	TimerCal m_BubbleSecondTimer;


	HPBar m_HPBar;
	bool m_Shot;
	bool m_MonsterBubble;
	bool m_Death;

private:
	// �浹
	ObjectCollision* pObjCol;
	ObjectCollision* p_MonsterUpCol;		// ��
	ObjectCollision* p_MonsterDownCol;		// �Ʒ�
	ObjectCollision* p_MonsterLeftCol;		// ����
	ObjectCollision* p_MonsterRightCol;		// ������


public:
	TileMapRenderer* m_TileRenderer;
	EditorTileMap* m_TileMap;

public:
	void Pos_Init();


private:
	enum MINIMONSTER_STATE
	{
		IDLE,
		RUN,
		ATTACK,
		DAMAGE,
		Death_01,
		Death_02,
		Death_03,
		Death_End,
		BubblePop,
		TEST,
		STATE_MAX
	};


	MINIMONSTER_STATE m_MonsterState;
	std::wstring Direction;		//  ����
	std::wstring AnimName[STATE_MAX];

public:
	std::wstring Get_Dir()
	{
		return Direction;
	}

public:
	void Idle();
	void Run();
	void Damage();
	void Bubble_First();

	void Monster_ChangeState(MINIMONSTER_STATE _State);


	void RandomDirection();
	std::wstring DirectionCheck();
	void Move();

	bool CanMove(std::wstring _Dir);

private:
	float m_MonsterSpeed;
	TimerCal m_WaitIdleTime;		// Idle->Run���� �ٲ�� �ð�
	TimerCal m_AttackTime;
	TimerCal m_RunToChangeTime;		// �޸��°� 5�ʵ���

private:
	bool m_bAttack;
	bool m_bChangeIdle;
	bool m_bIsBubble;
	bool m_bDeath;

public:
	void RandomAttackValue();

private:
	void Start_Update() override;
	void Prev_Update() override;
	void Update() override;
	void Late_Update() override;

	// �浹
	void Collision_Enter(ObjectCollision* _This, ObjectCollision* _Right) override;
	void Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other) override;
	void Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other) override;


private:
	std::set<__int64> m_BubbleIndex;			// ������ ���ٱ� �ε����� ������ set

public:
	void MonsterPosInit();
public:
	MonsterMini();
	~MonsterMini();
};

