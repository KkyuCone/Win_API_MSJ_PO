#pragma once
#include "ActorObjBase.h"
#include <map>
#include "TimerCal.h"
#include "Item.h"
#include <string>
#include "EditorTileMap.h"


class AnimationRenderer;
class SingleRenderer;
class Bubble;
class GameObjectImage;
class SoundControl;
class ObjectCollision;
class TileMapRenderer;
class InGameTimer;
class Player : public ActorObjBase
{
public:
	friend class MainSceneState;

public:
	InGameTimer* m_InGameTimer;

private:
	bool m_CharDie;


public:
	enum Character
	{
		Bazzi,
		Dao,
		Marid,
		Cappy,
		Max
	};

public:
	Character m_CharType;

	void SelectCharacterType();

public:
	void Character_Init(Character _Type);

public:
	void SelectCharacterRender(Character _Type);

private:
	// 캐릭터 능력치
	int m_Ruzzi;
	int m_BubbleCount;
	int m_WaterPower;
	float m_Speed;

	int m_BubbleMax;
	int m_WaterPowerMax;
	float m_SpeedMax;

	int m_CurBubbleCount;		// 현재 사용한 물풍선 개수


	// 디버프 및 탈것, 소모성 아이템, 버프(펀치, 신발)
	bool m_bDevil;
	bool m_bOwl;
	bool m_bSpaceship;
	bool m_bTurtle;


	bool m_bIsBubble;
	bool m_bDeath;

private:
	Item* m_pItem;
	std::map<std::wstring, Item*> m_GetItem;

public:
	void Set_Item(Item* _Item)
	{
		m_pItem = _Item;
	}
	void Set_UseItem(std::wstring _ItemName, Item::ITEM_TYPE _Type);

	std::wstring UseItem();

private:
	F_Rectangle m_Rectange;
	int m_SpriteSize;
	SingleRenderer* m_pTestRenderer;
	AnimationRenderer* m_pTestAniRenderer;
	AnimationRenderer* m_CharShadowRender;
	GameObjectImage* m_BGImage;
	SoundControl* m_SoundControl;
	SoundControl* m_ItemSoundControl;
	float Degree;

	bool m_bMoveUp;
	bool m_bMoveLeft;
	bool m_bMoveRight;
	bool m_bMoveDown;

	bool m_bMoveColUp;
	bool m_bMoveColLeft;
	bool m_bMoveColRight;
	bool m_bMoveColDown;

	// 움직이는 나무상자 애니메이션
	AnimationRenderer* m_UpMoveBoxAnimation;
	AnimationRenderer* m_DownMoveBoxAnimation;
	AnimationRenderer* m_LeftMoveBoxAnimation;
	AnimationRenderer* m_RightMoveBoxAnimation;

	int MoveBlockType = -1;
	F_Position CreateMoveBoxPos = F_Position{ -1,-1 };

	//
	TimerCal m_BombTimer;
	TimerCal m_DeathTimer;
	TimerCal m_ShakeTimer;

	bool m_bShake;


	// 콜라이더
	ObjectCollision* pObjCol;
	ObjectCollision* pPlayerColUp;
	ObjectCollision* pPlayerColUpLeft;
	ObjectCollision* pPlayerColUpRight;
	ObjectCollision* pPlayerColLeft;
	ObjectCollision* pPlayerColRight;
	ObjectCollision* pPlayerColDown;
	ObjectCollision* pPlayerColDownLeft;
	ObjectCollision* pPlayerColDownRight;

	enum INPUT_KEY
	{
		INPUT_UP,
		INPUT_LEFT,
		INPUT_RIGHT,
		INPUT_DOWN,
		INPUT_MAX
	};



	//////////////////////////////////////////////////// FSM
	enum FSM_STATE
	{
		IDLE,
		RUN,
		ATTACK,
		Death_01,
		Death_02,
		Death_03,
		Death_End,
		BubblePop,
		STATE_MAX
	};

	FSM_STATE m_PlayerState;
	std::wstring Direction;		//  방향
	std::wstring AnimName[STATE_MAX];

private:
	void Idle();
	void Run();
	void Attack();
	void Bubble_First();
	void Bubble_Second();
	void Bubble_Third();
	void Death();
	void Bubble_Pop();
	void Player_ChangeState(FSM_STATE _pState, bool Dir = true);

	void DirectionCheck();		// 방향체크
	void Move();				// 이동

public:
	void Check_BlockTile(INPUT_KEY _Key);
	void Block_Col_Animation(EditorTileMap::OBJTYPE _Type, F_Position _Pos);
	void Block_AnimationNoneItem(EditorTileMap::OBJTYPE _Type, F_Position _Pos);

private:
	std::map<__int64, Bubble*> m_BubbleMap;		// 이걸로 물풍선 중복 타일에 설치하지 못하도록 하기

public:
	void Erase_BubbleMap(VECTOR2_INT _Index);

public:
	TileMapRenderer* m_TileRenderer;
	EditorTileMap* m_TileMap;

public:
	Player();
	~Player();

private:
	void Start_Update() override;
	void Prev_Update() override;
	void Update() override;
	void Late_Update() override;

	void DebugRender() override;


private:
	void Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other) override;
	void Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other) override;
	void Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other) override;

public:
	void Item_Col(ObjectCollision* _Other);
	void Bubble_Col(ObjectCollision* _Other);

	void Pos_Init();

	void Character_PosInit();


	int MoveBubble = 0;



};

