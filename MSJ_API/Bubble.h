#pragma once
#include "ActorObjBase.h"
#include "TimerCal.h"
#include "EditorTileMap.h"
#include <vector>
#include <list>

class AnimationRenderer;
class TileMapRenderer;
class Player;
class Monster;
class SoundControl;
class Bubble : public ActorObjBase
{
public:
	friend class MainSceneState;

	enum BUBBLE_STATE
	{
		IDLE,
		BOMB,
		FADE,
		DEATH,
		OTHER,
		BUBBLE_MAX
	};


	enum BubbleType
	{
		Base_Bubble,
		Player_Bubble,
		Monster_Bubble
	};



private:
	Player* m_pPlayer;
	Monster* m_pMonster;
	VECTOR2_INT m_BubbleIndex;
	SoundControl* m_SoundControl;

	BubbleType m_BubbleType;

	bool m_bMonster;

private:
	int BubbleUpValue;
	int BubbleDownValue;
	int BubbleLeftValue;
	int BubbleRightValue;

public:
	void Set_Player(Player* _Player);
	void Set_BubbleIndex(VECTOR2_INT _Index);


	void Bubble::Set_Monster(Monster* _Mosnter);

private:
	BUBBLE_STATE m_BubbleState;
	std::wstring AnimName[BUBBLE_MAX];

private:
	TimerCal m_BombTimer;
	TimerCal m_FadeTimer;
	bool m_bBomb;

	AnimationRenderer* m_pTestAniRenderer;
	int m_BubblePower;
	float m_BubbleScale;

	ObjectCollision* pObjCol;

	std::vector<Bubble*> m_pBubbleBomb;


public:
	F_Position m_BubbleSize;


private:
	void Idle();
	void Bomb();
	void Fade();
	void Bubble_Death();

	void Bubble_ChangeState(wchar_t* _pStateName);

	void Block_Col_Animation(EditorTileMap::OBJTYPE _Type, F_Position _Pos);

public:
	TileMapRenderer* m_TileRenderer;
	EditorTileMap* m_TileMap;

public:
	void ChangeColName(std::wstring _Name);

public:
	void Set_BubbleCount(int _Count);

public:
	void BubbleState_Change();

private:
	VECTOR2_INT m_BubbleUpIndex;
	VECTOR2_INT m_BubbleDownIndex;
	VECTOR2_INT m_BubbleLeftIndex;
	VECTOR2_INT m_BubbleRightIndex;

public:
	Bubble();
	~Bubble();

private:
	void Start_Update() override;
	void Prev_Update() override;
	void Update() override;
	void Late_Update() override;

public:
	void Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other) override;
	void Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other) override;
	void Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other) override;

public:
	void BubbleType_Init(int a = 0);
	void Bubble_Init(BubbleType _Type);

};

