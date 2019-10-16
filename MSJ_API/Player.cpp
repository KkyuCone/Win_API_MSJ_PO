#include "stdafx.h"
#include "Player.h"
#include "Util_Core.h"
#include "MainSceneState.h"
#include "SingleRenderer.h"
#include "AnimationRenderer.h"
#include "ResourceManager.h"
#include "GameCoreMath.h"
#include "ObjectCollision.h"
#include "TileMapRenderer.h"
#include "Bubble.h"
#include "Resource.h"
#include "GameObjectImage.h"
#include "SoundControl.h"
#include "InGameTimer.h"
#include "ObjTile.h"
#include <string>

#define PIMAGE_CUT 10*1

///////////////////////////////////////////////////////////////// 생성자, 소멸자

Player::Player()
	: m_Rectange{ {0.0f, 0.0f}, { 100.0f, 100.0f } }, m_pTestRenderer(nullptr), m_SpriteSize(0), Degree(0.0f)
	, m_Speed(120.0f), m_bMoveUp(true), m_bMoveLeft(true), m_bMoveRight(true), m_bMoveDown(true)
	, m_bMoveColUp(true), m_bMoveColLeft(true), m_bMoveColRight(true), m_bMoveColDown(true),
	m_CharType(Max), m_Ruzzi(0), m_BubbleCount(0), m_WaterPower(0),
	m_BubbleMax(0), m_WaterPowerMax(0), m_SpeedMax(0.0f),
	m_bDevil(false), m_bOwl(false), m_bSpaceship(false), m_bTurtle(false),
	m_CurBubbleCount(0), m_BombTimer(2.0f), m_DeathTimer(1.5f), m_bDeath(false), m_bIsBubble(false), 
	m_pItem(nullptr), m_ShakeTimer(0.5f), m_bShake(true), m_CharDie(false)
	, m_UpMoveBoxAnimation(nullptr), m_DownMoveBoxAnimation(nullptr), m_LeftMoveBoxAnimation(nullptr), m_RightMoveBoxAnimation(false)
{
	SelectCharacterType();
	Character_Init(m_CharType);
	Character_PosInit();
	//VECTOR2_INT Index = m_TileRenderer->OriginTileIndex(m_BasePos);
	m_PlayerState = RUN;
}


Player::~Player()
{
}


///////////////////////////////////////////////////////////////// Update

void Player::SelectCharacterType()
{
	m_CharType = (Character)MainSceneState::m_GameChar_Type;
}

void Player::Start_Update()
{

	// 사운드
	m_SoundControl = ResourceManager::Instance().SoundControl_Insert();
	m_ItemSoundControl = ResourceManager::Instance().SoundControl_Insert();

	AnimName[IDLE] = L"Idle";
	AnimName[RUN] = L"Run";
	AnimName[ATTACK] = L"Attack";
	AnimName[Death_01] = L"Death_01";
	AnimName[Death_02] = L"Death_02";
	AnimName[Death_03] = L"Death_03";
	AnimName[Death_End] = L"Death_End";
	AnimName[BubblePop] = L"BubblePop";

	Direction = L"D";

	// 충돌
	pObjCol = Create_Collision(L"Player");
	pObjCol->Name = L"Player";
	pObjCol->Pivot(F_Position(0, 22));
	pObjCol->Size(F_Position(40, 35));
	//pObjCol->Size(F_Position(10, 10));

	pPlayerColUp = Create_Collision(L"Player_Up");
	pPlayerColUp->Name = L"Player_Up";
	pPlayerColUp->Pivot(F_Position(0, -4.5f));
	pPlayerColUp->Size(F_Position(10, 10));

	pPlayerColUpLeft = Create_Collision(L"Player_UpLeft");
	pPlayerColUpLeft->Name = L"Player_UpLeft";
	pPlayerColUpLeft->Pivot(F_Position(-25.0f, -4.5f));
	pPlayerColUpLeft->Size(F_Position(10, 10));

	pPlayerColUpRight = Create_Collision(L"Player_UpRight");
	pPlayerColUpRight->Name = L"Player_UpRight";
	pPlayerColUpRight->Pivot(F_Position(25.0f, -4.5f));
	pPlayerColUpRight->Size(F_Position(10, 10));

	pPlayerColLeft = Create_Collision(L"Player_Left");
	pPlayerColLeft->Name = L"Player_Left";
	pPlayerColLeft->Pivot(F_Position(-25.0f, 20));
	pPlayerColLeft->Size(F_Position(10, 10));

	pPlayerColRight = Create_Collision(L"Player_Right");
	pPlayerColRight->Name = L"Player_Right";
	pPlayerColRight->Pivot(F_Position(25.0f, 20));
	pPlayerColRight->Size(F_Position(10, 10));

	pPlayerColDown = Create_Collision(L"Player_Down");
	pPlayerColDown->Name = L"Player_Down";
	pPlayerColDown->Pivot(F_Position(0, 50));
	pPlayerColDown->Size(F_Position(10, 10));

	pPlayerColDownLeft = Create_Collision(L"Player_DownLeft");
	pPlayerColDownLeft->Name = L"Player_DownLeft";
	pPlayerColDownLeft->Pivot(F_Position(-25.0f, 50));
	pPlayerColDownLeft->Size(F_Position(10, 10));

	pPlayerColDownRight = Create_Collision(L"Player_DownRight");
	pPlayerColDownRight->Name = L"Player_DownRight";
	pPlayerColDownRight->Pivot(F_Position(25.0f, 50));
	pPlayerColDownRight->Size(F_Position(10, 10));

	// 렌더
	SelectCharacterRender(m_CharType);


	Player_ChangeState(IDLE);


	// 그림자

	m_CharShadowRender = Create_Renderer<AnimationRenderer>(10);
	m_CharShadowRender->Pivot(F_Position{ -2,6 });
	m_CharShadowRender->Size(F_Position{ 100, 100 });
	m_CharShadowRender->Animation_Create(L"CharShadow", L"PlayerShadow.bmp", 0, 0, true);
	m_CharShadowRender->Set_Alpha(150);
	m_CharShadowRender->Animation_Change(L"CharShadow");


}


void Player::Prev_Update()
{
}

void Player::Update()
{
	if (true == m_CharDie)
	{
		return;
	}


	DirectionCheck();

	// 애니메이션 상태에 따른 함수 호출
	switch (m_PlayerState)
	{
	case Player::IDLE:
		Idle();
		MoveBubble = 0;
		break;
		
	case Player::RUN:
		Run();
		break;

	case Player::ATTACK:
		Attack();
		break;

	case Player::Death_01:
		Bubble_First();
		break;

	case Player::Death_02:
		Bubble_Second();
		break;

	case Player::Death_03:
		Bubble_Third();
		break;

	case Player::Death_End:
		Death();
		break;

	case Player::BubblePop:
		Bubble_Pop();
		break;

	default:
		break;
	}


	if (true == InputManager::Instance().Down(L"Bubble"))
	{
		if (m_CurBubbleCount >= m_BubbleCount)
		{
			return;
		}

		F_Position CharBasePos = m_BasePos;

		F_Position BubblePos = m_TileRenderer->OriginTilePos(CharBasePos += F_Position{ 0, 30 });
		VECTOR2_INT BubbleIndex = m_TileRenderer->OriginTileIndex(CharBasePos += F_Position{ 0, 30 });


		std::map<__int64, Bubble*>::iterator Start = m_BubbleMap.begin();
		std::map<__int64, Bubble*>::iterator End = m_BubbleMap.end();

		for (; Start != End; ++Start)
		{
			// 이미 물풍선이 있다면 return
			if (Start->first == BubbleIndex)
			{
				return;
			}

		}

		Bubble* pNewBubble = Stage()->Create_Actor<Bubble>();
		pNewBubble->ChangeColName(L"Bubble");
		pNewBubble->Set_BubbleCount(m_WaterPower);
		pNewBubble->m_TileMap = m_TileMap;
		pNewBubble->m_TileRenderer = m_TileRenderer;
		pNewBubble->Pos(BubblePos);
		pNewBubble->Set_BubbleIndex(BubbleIndex);
		pNewBubble->Set_Player(this);
		m_BubbleMap.insert(std::map<__int64, Bubble*>::value_type(BubbleIndex, pNewBubble));

		++m_CurBubbleCount;

		m_SoundControl->Sound_NewPlay(L"BubbleInstall.ogg");
		m_SoundControl->Sound_SetPitch(1.0f);
	}

	// 아이템 사용시 빈 이미지로 교체
	if (true == InputManager::Instance().Down(L"Ctrl"))
	{
		std::wstring ItemName = UseItem();

		if (ItemName == L"Needle_Get")
		{
			//m_GetItem.clear();						// 사용한 아이템 제거
			//return;
		}

		m_pItem->Change_ItemImage(L"Empty_Item", Item::ITEM_TYPE::Emtpy_Item);
		m_pItem->ItemState.m_bItem = false;
	}
}

void Player::Late_Update()
{
	// 음악 다시 시작
	//if (true == InputManager::Instance().Down(L"Up"))
	//{
	//	m_SoundControl->Sound_NewPlay(L"bg_3.ogg");
	//}

	 // 콜라이더 끄기
	if (true == InputManager::Instance().DownStay(L"KEY_F12"))
	{
		Stage()->DebugCol_Off();
	}

	if (true == InputManager::Instance().DownStay(L"KEY_F11"))
	{
		Stage()->DebugCol_On();
	}


	//m_Rectange.Position = m_BasePos;
	//m_Rectange.Position = m_pTestAniRenderer->RenderPos();
	//Rectangle(BHDC, m_Rectange.I_Left(), m_Rectange.I_Top(), m_Rectange.I_Right(), m_Rectange.I_Botton());

	Rectangle(BHDC, 0, 0, 1024, 768);
	m_Rectange.Position = m_pTestAniRenderer->RenderPos();

	wchar_t OutText[100];
	swprintf_s(OutText, L"PlayerDegree : %f ", Degree);
	TextOutW(BHDC, 200, 40, OutText, lstrlenW(OutText));

	swprintf_s(OutText, L"마우스 거리 : %f ", GameCoreMath::Hypotenuse(ScreenPos(), InputManager::Instance().MousePos_F()));
	TextOutW(BHDC, 200, 60, OutText, lstrlenW(OutText));

	swprintf_s(OutText, L"각도 : %f ", GameCoreMath::PtoP_Degree(ScreenPos(), InputManager::Instance().MousePos_F()));
	TextOutW(BHDC, 200, 80, OutText, lstrlenW(OutText));

	swprintf_s(OutText, L"스크린포스 : %f %f", ScreenPos().X, ScreenPos().Y);
	TextOutW(BHDC, 200, 100, OutText, lstrlenW(OutText));

	swprintf_s(OutText, L"마우스포스 : %f %f", InputManager::Instance().MousePos_F().X, InputManager::Instance().MousePos_F().Y);
	TextOutW(BHDC, 200, 120, OutText, lstrlenW(OutText));

	POINT Arr_Point[2];
	Arr_Point[0].x = (LONG)ScreenPos().X;
	Arr_Point[0].y = (LONG)ScreenPos().Y;

	F_Position Dir = GameCoreMath::DegreeRotPos(Degree);
	Dir *= 200.0f;

	Arr_Point[1].x = (LONG)(Dir.X + Arr_Point[0].x);
	Arr_Point[1].y = (LONG)(Dir.Y + Arr_Point[0].y);

	Polygon(BHDC, Arr_Point, 2);


}

void Player::DebugRender()
{
}



/////////////////////////////////////////////////////////////// Animation


void Player::Player_ChangeState(FSM_STATE _pState, bool Dir)
{
	std::wstring Ani_Name;

	if (true == Dir)
	{
		Ani_Name = Direction + AnimName[_pState];
	}
	else
	{
		Ani_Name = AnimName[_pState];
	}

	m_pTestAniRenderer->Animation_Change(Ani_Name.c_str());
	m_PlayerState = _pState;
}

void Player::DirectionCheck()
{
	if (true == m_bIsBubble)
	{
		return;
	}

	std::wstring CheckDir = Direction;

	if (true == InputManager::Instance().DownStay(L"Left"))
	{
		CheckDir = L"L";
	}
	else if (true == InputManager::Instance().DownStay(L"Right"))
	{
		CheckDir = L"R";
	}
	else if (true == InputManager::Instance().DownStay(L"Up"))
	{
		CheckDir = L"U";
	}
	else if (true == InputManager::Instance().DownStay(L"Down"))
	{
		CheckDir = L"D";
	}

	if (CheckDir != Direction)
	{
		if (true == m_bDeath)
		{
			return;
		}

		std::wstring Ani_Name = CheckDir + AnimName[m_PlayerState];
		m_pTestAniRenderer->Animation_Change(Ani_Name.c_str());
		Direction = CheckDir;
	}
}

// 이동시에 블럭이 있는지 확인
void Player::Check_BlockTile(INPUT_KEY _Key)
{
	EditorTileMap::OBJTYPE ObjIndex = EditorTileMap::OBJTYPE::NONE;
	int ObjIndexInt = 0;

	VECTOR2_INT PositionIndex = { -1, -1 };
	F_Position AniBlcokPos = { -1, -1 };

	bool Mid = true;
	bool Left = true;
	bool Right = true;

	int TransferableBlock = -2;
	F_Position TransferableBlockPos = { -1, -1 };


	switch (_Key)
	{
	case Player::INPUT_UP:
		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColUp->ParentPos());
		Mid = m_TileRenderer->Find_BlockTile(PositionIndex);

		TransferableBlock = m_TileRenderer->Find_BlockMove(PositionIndex, L"UP");					// 나무상자가 있는지 확인 -> 밀어내기

		if (TransferableBlock != -2)
		{
			PositionIndex = (VECTOR2_INT)PositionIndex + VECTOR2_INT{ 0, -1 };
			TransferableBlockPos = m_TileRenderer->OriginTilePos(PositionIndex);
			MoveBlockType = TransferableBlock;
			m_TileMap->CreateMoveObjIndex((EditorTileMap::OBJTYPE)TransferableBlock, TransferableBlockPos, L"UP");
		}

		ObjIndexInt = (m_TileRenderer->Find_MoveBlockTile(PositionIndex));		// 타일 이동 블럭

		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColUpLeft->ParentPos());
		Left = m_TileRenderer->Find_BlockTile(PositionIndex);

		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColUpRight->ParentPos());
		Right = m_TileRenderer->Find_BlockTile(PositionIndex);

		if (true == Left && false == Right)
		{
			m_bMoveUp = false;
			m_BasePos += F_Position::LEFT * TimeManager::Instance().DeltaTime() * m_Speed;
		}
		else if (false == Left && true == Right)
		{
			m_bMoveUp = false;
			m_BasePos += F_Position::RIGHT * TimeManager::Instance().DeltaTime() * m_Speed;
		}

		if (false == Mid && false == Left && false == Right)
		{
			m_bMoveUp = false;
		}
		else if (true == Mid && true == Left && true == Right)
		{
			m_bMoveUp = true;

		}
		break;
	case Player::INPUT_LEFT:
		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColLeft->ParentPos());
		Mid = m_TileRenderer->Find_BlockTile(PositionIndex);

		// 나무상자
		TransferableBlock = m_TileRenderer->Find_BlockMove(PositionIndex, L"LEFT");					// 나무상자가 있는지 확인 -> 밀어내기

		if (TransferableBlock != -2)
		{
			PositionIndex = (VECTOR2_INT)PositionIndex + VECTOR2_INT{ -1, -0 };
			TransferableBlockPos = m_TileRenderer->OriginTilePos(PositionIndex);
			MoveBlockType = TransferableBlock;
			m_TileMap->CreateMoveObjIndex((EditorTileMap::OBJTYPE)TransferableBlock, TransferableBlockPos, L"LEFT");
		}
		ObjIndexInt = (m_TileRenderer->Find_MoveBlockTile(PositionIndex));

		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColDownLeft->ParentPos());			// 
		Left = m_TileRenderer->Find_BlockTile(PositionIndex);
		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColUpLeft->ParentPos() + F_Position{ 0,5 });
		Right = m_TileRenderer->Find_BlockTile(PositionIndex);

		if (true == Left && false == Right)
		{
			m_bMoveLeft = false;

			if (true == m_bMoveColDown)
			{
				m_BasePos += F_Position::DOWN * TimeManager::Instance().DeltaTime() * m_Speed;
			}
		}
		else if (false == Left && true == Right)
		{
			m_bMoveLeft = false;

			if (true == m_bMoveColUp)
			{
				m_BasePos += F_Position::UP * TimeManager::Instance().DeltaTime() * m_Speed;
			}
		}

		if (false == Mid && false == Left && false == Right)
		{
			m_bMoveLeft = false;
		}
		else if (true == Mid && true == Left && true == Right)
		{
			m_bMoveLeft = true;
		}

		if (false == m_bMoveColLeft)
		{
			m_bMoveRight = false;
		}

		break;
	case Player::INPUT_RIGHT:
		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColRight->ParentPos());
		Mid = m_TileRenderer->Find_BlockTile(PositionIndex);

		// 나무상자
		TransferableBlock = m_TileRenderer->Find_BlockMove(PositionIndex, L"RIGHT");					// 나무상자가 있는지 확인 -> 밀어내기

		if (TransferableBlock != -2)
		{
			PositionIndex = (VECTOR2_INT)PositionIndex + VECTOR2_INT{ 1, 0 };
			TransferableBlockPos = m_TileRenderer->OriginTilePos(PositionIndex);
			MoveBlockType = TransferableBlock;
			m_TileMap->CreateMoveObjIndex((EditorTileMap::OBJTYPE)TransferableBlock, TransferableBlockPos, L"RIGHT");
		}

		ObjIndexInt = (m_TileRenderer->Find_MoveBlockTile(PositionIndex));

		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColUpRight->ParentPos() + F_Position{ 0,5 });			// 
		Left = m_TileRenderer->Find_BlockTile(PositionIndex);
		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColDownRight->ParentPos());
		Right = m_TileRenderer->Find_BlockTile(PositionIndex);

		if (true == Left && false == Right)
		{
			m_bMoveRight = false;
			
			if (true == m_bMoveColUp)
			{
				m_BasePos += F_Position::UP * TimeManager::Instance().DeltaTime() * m_Speed;
			}
		}
		else if (false == Left && true == Right)
		{
			m_bMoveRight = false;

			if (true == m_bMoveColDown)
			{
				m_BasePos += F_Position::DOWN * TimeManager::Instance().DeltaTime() * m_Speed;
			}
		}

		if (false == Mid && false == Left && false == Right)
		{
			m_bMoveRight = false;
		}
		else if (true == Mid && true == Left && true == Right)
		{
			m_bMoveRight = true;
		}

		if (false == m_bMoveColRight)
		{
			m_bMoveRight = false;
		}

		break;
	case Player::INPUT_DOWN:
		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColDown->ParentPos());
		Mid = m_TileRenderer->Find_BlockTile(PositionIndex);

		// 나무상자
		TransferableBlock = m_TileRenderer->Find_BlockMove(PositionIndex, L"DOWN");					// 나무상자가 있는지 확인 -> 밀어내기

		if (TransferableBlock != -2)
		{
			PositionIndex = (VECTOR2_INT)PositionIndex + VECTOR2_INT{ 0, 1 };
			TransferableBlockPos = m_TileRenderer->OriginTilePos(PositionIndex);
			MoveBlockType = TransferableBlock;
			//MoveBoxAnimation_Init(L"DOWN", PositionIndex);
			m_TileMap->CreateMoveObjIndex((EditorTileMap::OBJTYPE)TransferableBlock, TransferableBlockPos, L"DOWN");
		}

		ObjIndexInt = (m_TileRenderer->Find_MoveBlockTile(PositionIndex));


		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColDownLeft->ParentPos());			// 
		Left = m_TileRenderer->Find_BlockTile(PositionIndex);
		PositionIndex = m_TileRenderer->OriginTileIndex(pPlayerColDownRight->ParentPos());
		Right = m_TileRenderer->Find_BlockTile(PositionIndex);

		if (true == Left && false == Right)
		{
			m_bMoveDown = false;
			m_BasePos += F_Position::LEFT * TimeManager::Instance().DeltaTime() * m_Speed;
		}
		else if (false == Left && true == Right)
		{
			m_bMoveDown = false;
			m_BasePos += F_Position::RIGHT * TimeManager::Instance().DeltaTime() * m_Speed;
		}

		if (false == Mid && false == Left && false == Right)
		{
			m_bMoveDown = false;
		}
		else if (true == Mid && true == Left && true == Right)
		{
			m_bMoveDown = true;
		}

		break;
	case Player::INPUT_MAX:
		break;
	default:
		break;
	}

	if (false == m_bShake)
	{
		if (true == m_ShakeTimer.TimerCheck())
		{
			m_bShake = true;
			m_ShakeTimer.TimerReset();
		}
	}

	if (true == m_bShake)
	{
		ObjIndex = (EditorTileMap::OBJTYPE)ObjIndexInt;

		// 흔들리는 나무, 텐트 애니메이션 실행
		switch (ObjIndex)
		{
		case EditorTileMap::CAMP_BLOCK_04:
		case EditorTileMap::CAMP_BLOCK_05:
		case EditorTileMap::CAMP_OBJECT_00:
		case EditorTileMap::CAMP_OBJECT_01:
		case EditorTileMap::VILAGE_BLOCK_03:
			AniBlcokPos = m_TileRenderer->OriginTilePos(PositionIndex);
			Block_AnimationNoneItem(ObjIndex, AniBlcokPos);
			m_bShake = false;
			break;
		default:
			break;
		}
	}
}

// 흔들리는 나무, 텐트 이동시 애니메이션 실행
void Player::Block_Col_Animation(EditorTileMap::OBJTYPE _Type, F_Position _Pos)
{
	m_TileMap->Block_Animation(_Type, _Pos);
}

void Player::Block_AnimationNoneItem(EditorTileMap::OBJTYPE _Type, F_Position _Pos)
{
	m_TileMap->Block_AnimationNoneItem(_Type, _Pos);
}

void Player::Move()
{
	int WoodenBox = -2;

	if (true == InputManager::Instance().DownStay(L"Left"))
	{
		Check_BlockTile(INPUT_KEY::INPUT_LEFT);

		if (false == m_bMoveLeft || false == m_bMoveColLeft)
		{
			return;
		}

		m_BasePos += F_Position::LEFT * TimeManager::Instance().DeltaTime() * m_Speed;
	}
	else if(true == InputManager::Instance().DownStay(L"Right"))
	{
		Check_BlockTile(INPUT_KEY::INPUT_RIGHT);
		if (false == m_bMoveRight || false == m_bMoveColRight)
		{
			return;
		}
		m_BasePos += F_Position::RIGHT * TimeManager::Instance().DeltaTime() * m_Speed;
	}
	else if (true == InputManager::Instance().DownStay(L"Up"))
	{
		Check_BlockTile(INPUT_KEY::INPUT_UP);

		if (false == m_bMoveUp || false == m_bMoveColUp)
		{
			return;
		}


		m_BasePos += F_Position::UP * TimeManager::Instance().DeltaTime() * m_Speed;
	}
	else if (true == InputManager::Instance().DownStay(L"Down"))
	{
		Check_BlockTile(INPUT_KEY::INPUT_DOWN);

		if (false == m_bMoveDown || false == m_bMoveColDown)
		{
			return;
		}

		m_BasePos += F_Position::DOWN * TimeManager::Instance().DeltaTime() * m_Speed;
	}
}


// 충돌

void Player::Collision_Enter(ObjectCollision* _This, ObjectCollision* _Other)
{
	// 맵 이동 제한 (맵의 상하좌우)
	if (_This->Name == L"Player_Up" && _Other->Name == L"Limit_Up" )
	{
		m_bMoveColUp = false;
	}
	else if (_This->Name == L"Player_Left" && _Other->Name == L"Limit_Left")
	{
		m_bMoveColLeft = false;
	}
	else if (_This->Name == L"Player_Right" && _Other->Name == L"Limit_Right")
	{
		m_bMoveColRight = false;
	}
	else if (_This->Name == L"Player_Down" && _Other->Name == L"Limit_Down")
	{
		m_bMoveColDown = false;
	}



	// 아이템 획득시
	if (_This->Name == L"Player")
	{
		Item_Col( _Other);
		Bubble_Col(_Other);
	}

}

void Player::Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other)
{

}
void Player::Collision_Exit(ObjectCollision* _This, ObjectCollision* _Other)
{
	if (_This->Name == L"Player_Up" && _Other->Name == L"Limit_Up")
	{
		m_bMoveColUp = true;
	}

	if (_This->Name == L"Player_Left" && _Other->Name == L"Limit_Left")
	{
		m_bMoveColLeft = true;
	}

	if (_This->Name == L"Player_Right" && _Other->Name == L"Limit_Right")
	{
		m_bMoveColRight = true;
	}

	if (_This->Name == L"Player_Down" && _Other->Name == L"Limit_Down")
	{
		m_bMoveColDown = true;
	}
}





void Player::Item_Col(ObjectCollision* _Other)
{

	if (_Other->Name == L"Gold_Coin")
	{
		m_ItemSoundControl->Sound_NewPlay(L"Coin.ogg");
		m_ItemSoundControl->Sound_SetPitch(1.0f);
		m_Ruzzi += 50;
		_Other->Object()->Obj_Death();
		return;
	}
	else if (_Other->Name == L"Silver_Coin")
	{
		m_ItemSoundControl->Sound_NewPlayItem(L"Coin.ogg");
		m_ItemSoundControl->Sound_SetPitch(1.0f);
		m_Ruzzi += 20;
		_Other->Object()->Obj_Death();
		return;
	}
	else if (_Other->Name == L"Bronze_Coin")
	{
		m_ItemSoundControl->Sound_NewPlayItem(L"Coin.ogg");
		m_ItemSoundControl->Sound_SetPitch(1.0f);
		m_Ruzzi += 10;
		_Other->Object()->Obj_Death();
		return;
	}
	else if (_Other->Name == L"Gold_CoinPurse")
	{
		m_ItemSoundControl->Sound_NewPlayItem(L"Coin.ogg");
		m_ItemSoundControl->Sound_SetPitch(1.0f);
		m_Ruzzi += 500;
		_Other->Object()->Obj_Death();
		return;
	}
	else if (_Other->Name == L"Silver_CoinPurse")
	{
		m_ItemSoundControl->Sound_NewPlayItem(L"Coin.ogg");
		m_ItemSoundControl->Sound_SetPitch(1.0f);
		m_Ruzzi += 200;
		_Other->Object()->Obj_Death();
		return;
	}
	else if (_Other->Name == L"Bronze_CoinPurse")
	{
		m_ItemSoundControl->Sound_NewPlayItem(L"Coin.ogg");
		m_ItemSoundControl->Sound_SetPitch(1.0f);
		m_Ruzzi += 100;
		_Other->Object()->Obj_Death();
		return;
	}
	else if (_Other->Name == L"Water_Balloon")
	{
		++m_BubbleCount;

		if (m_BubbleCount >= m_BubbleMax)
		{
			m_BubbleCount = m_BubbleMax;
		}
		_Other->Object()->Obj_Death();

	}
	else if (_Other->Name == L"Potion")
	{
		++m_WaterPower;

		if (m_WaterPower >= m_WaterPowerMax)
		{
			m_WaterPower = m_WaterPowerMax;
		}
		_Other->Object()->Obj_Death();
	}
	else if (_Other->Name == L"MegaBomb")
	{
		m_WaterPower = m_WaterPowerMax;
		_Other->Object()->Obj_Death();
	}
	else if (_Other->Name == L"RollerSkates")
	{
		m_Speed += (SPEED_INIT * 1.0f);

		if (m_Speed >= m_SpeedMax)
		{
			m_Speed = m_SpeedMax;
		}
		_Other->Object()->Obj_Death();
	}
	else if (_Other->Name == L"Needle")
	{
		Set_UseItem(L"Needle", Item::ITEM_TYPE::Needle);
		_Other->Object()->Obj_Death();
	}
	else if (_Other->Name == L"Sneakers")
	{
		_Other->Object()->Obj_Death();
	}
	else if (_Other->Name == L"RedDevil")
	{
		m_Speed = m_SpeedMax;
		_Other->Object()->Obj_Death();
	}
	else
	{
		return;
	}

	m_ItemSoundControl->Sound_NewPlayItem(L"EatItem_01.ogg");
	m_ItemSoundControl->Sound_SetPitch(1.0f);
}

// 캐릭터 타입
void Player::Character_Init(Character _Type)
{
	switch (_Type)
	{
	case Player::Bazzi:
	{
		m_Ruzzi = RUZZI_INIT;
		m_BubbleCount = BUBBLECOUNT_INIT * 1;
		m_WaterPower = WATERPOWER_INIT * 1;
		m_Speed = (SPEED_INIT * 5.0f);

		m_BubbleMax = 6;
		m_WaterPowerMax = 7;
		m_SpeedMax = (SPEED_INIT * 9.0f);
		break;
	}
	case Player::Dao:
	{
		m_Ruzzi = RUZZI_INIT;
		m_BubbleCount = BUBBLECOUNT_INIT * 1;
		m_WaterPower = WATERPOWER_INIT * 1;
		m_Speed = (SPEED_INIT * 5.0f);

		m_BubbleMax = 10;
		m_WaterPowerMax = 7;
		m_SpeedMax = (SPEED_INIT * 7.0f);
		break;
	}
	case Player::Marid:
	{
		m_Ruzzi = RUZZI_INIT;
		m_BubbleCount = BUBBLECOUNT_INIT * 2;
		m_WaterPower = WATERPOWER_INIT * 1;
		m_Speed = (SPEED_INIT * 4.0f);

		m_BubbleMax = 9;
		m_WaterPowerMax = 6;
		m_SpeedMax = (SPEED_INIT * 8.0f);
		break;
	}
	case Player::Cappy:
	{
		m_Ruzzi = RUZZI_INIT;
		m_BubbleCount = BUBBLECOUNT_INIT * 1;
		m_WaterPower = WATERPOWER_INIT * 2;
		m_Speed = (SPEED_INIT * 4.0f);

		m_BubbleMax = 9;
		m_WaterPowerMax = 8;
		m_SpeedMax = (SPEED_INIT * 8.0f);
		break;
	}
	default:
		break;
	}
}

void Player::SelectCharacterRender(Character _Type)
{
	switch (_Type)
	{
	case Player::Bazzi:
		// 렌더
		m_pTestAniRenderer = Create_Renderer<AnimationRenderer>(11);
		m_pTestAniRenderer->Size(F_Position{ 100, 100 });

		m_pTestAniRenderer->Animation_Create(L"UIdle", L"unit_bazzi.bmp", 0, 0, true);
		m_pTestAniRenderer->Animation_Create(L"URun", L"unit_bazzi.bmp", 1, 5, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"UAttack", L"unit_bazzi.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"DIdle", L"unit_bazzi.bmp", 5, 5, true);
		m_pTestAniRenderer->Animation_Create(L"DRun", L"unit_bazzi.bmp", 6, 10, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"DAttack", L"unit_bazzi.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"RIdle", L"unit_bazzi.bmp", 15, 15, true);
		m_pTestAniRenderer->Animation_Create(L"RRun", L"unit_bazzi.bmp", 16, 20, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"RAttack", L"unit_bazzi.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"LIdle", L"unit_bazzi.bmp", 10, 10, true);
		m_pTestAniRenderer->Animation_Create(L"LRun", L"unit_bazzi.bmp", 11, 15, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"LAttack", L"unit_bazzi.bmp", 20, 29, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"Death_01", L"unit_bazzi.bmp", 20, 26, false, 0.15f);	// 물풍선되기1
		m_pTestAniRenderer->Animation_Create(L"Death_02", L"unit_bazzi.bmp", 24, 27, true, 0.15f);	// 물풍선되기2 (반복구간)
		m_pTestAniRenderer->Animation_Create(L"Death_03", L"unit_bazzi.bmp", 24, 27, false, 0.15f);	// 물풍선되기3 (사망구간)
		m_pTestAniRenderer->Animation_Create(L"Death_End", L"unit_bazzi.bmp", 31, 34, false, 0.1f);				// 사망
		m_pTestAniRenderer->Animation_Create(L"Death_Effect", L"unit_bazzi.bmp", 35, 35, false, 0.1f);				// 사망 이펙트

		m_pTestAniRenderer->Animation_Create(L"BubblePop", L"unit_bazzi.bmp", 27, 29, false, 0.1f);				// 물풍선 터트리기
		m_pTestAniRenderer->Animation_Create(L"Pop_Effect", L"unit_bazzi.bmp", 30, 30, false, 0.1f);				// 물풍선 터트릴때 이펙트
		break;
	case Player::Dao:
		// 렌더
		m_pTestAniRenderer = Create_Renderer<AnimationRenderer>(11);
		m_pTestAniRenderer->Size(F_Position{ 100, 100 });

		m_pTestAniRenderer->Animation_Create(L"UIdle", L"unit_dao.bmp", 0, 0, true);
		m_pTestAniRenderer->Animation_Create(L"URun", L"unit_dao.bmp", 1, 5, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"UAttack", L"unit_dao.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"DIdle", L"unit_dao.bmp", 5, 5, true);
		m_pTestAniRenderer->Animation_Create(L"DRun", L"unit_dao.bmp", 6, 10, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"DAttack", L"unit_dao.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"RIdle", L"unit_dao.bmp", 15, 15, true);
		m_pTestAniRenderer->Animation_Create(L"RRun", L"unit_dao.bmp", 16, 20, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"RAttack", L"unit_dao.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"LIdle", L"unit_dao.bmp", 10, 10, true);
		m_pTestAniRenderer->Animation_Create(L"LRun", L"unit_dao.bmp", 11, 15, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"LAttack", L"unit_dao.bmp", 20, 29, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"Death_01", L"unit_dao.bmp", 20, 26, false, 0.15f);	// 물풍선되기1
		m_pTestAniRenderer->Animation_Create(L"Death_02", L"unit_dao.bmp", 24, 27, true, 0.15f);	// 물풍선되기2 (반복구간)
		m_pTestAniRenderer->Animation_Create(L"Death_03", L"unit_dao.bmp", 24, 27, false, 0.15f);	// 물풍선되기3 (사망구간)
		m_pTestAniRenderer->Animation_Create(L"Death_End", L"unit_dao.bmp", 31, 34, false, 0.1f);				// 사망
		m_pTestAniRenderer->Animation_Create(L"Death_Effect", L"unit_dao.bmp", 35, 35, false, 0.1f);				// 사망 이펙트

		m_pTestAniRenderer->Animation_Create(L"BubblePop", L"unit_dao.bmp", 27, 29, false, 0.1f);				// 물풍선 터트리기
		m_pTestAniRenderer->Animation_Create(L"Pop_Effect", L"unit_dao.bmp", 30, 30, false, 0.1f);				// 물풍선 터트릴때 이펙트
		break;
	case Player::Marid:
		// 렌더
		m_pTestAniRenderer = Create_Renderer<AnimationRenderer>(11);
		m_pTestAniRenderer->Size(F_Position{ 100, 100 });

		m_pTestAniRenderer->Animation_Create(L"UIdle", L"unit_luxmarid.bmp", 0, 0, true);
		m_pTestAniRenderer->Animation_Create(L"URun", L"unit_luxmarid.bmp", 1, 5, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"UAttack", L"unit_luxmarid.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"DIdle", L"unit_luxmarid.bmp", 5, 5, true);
		m_pTestAniRenderer->Animation_Create(L"DRun", L"unit_luxmarid.bmp", 6, 10, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"DAttack", L"unit_luxmarid.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"RIdle", L"unit_luxmarid.bmp", 15, 15, true);
		m_pTestAniRenderer->Animation_Create(L"RRun", L"unit_luxmarid.bmp", 16, 20, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"RAttack", L"unit_luxmarid.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"LIdle", L"unit_luxmarid.bmp", 10, 10, true);
		m_pTestAniRenderer->Animation_Create(L"LRun", L"unit_luxmarid.bmp", 11, 15, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"LAttack", L"unit_luxmarid.bmp", 20, 29, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"Death_01", L"unit_luxmarid.bmp", 20, 26, false, 0.15f);	// 물풍선되기1
		m_pTestAniRenderer->Animation_Create(L"Death_02", L"unit_luxmarid.bmp", 24, 27, true, 0.15f);	// 물풍선되기2 (반복구간)
		m_pTestAniRenderer->Animation_Create(L"Death_03", L"unit_luxmarid.bmp", 24, 27, false, 0.15f);	// 물풍선되기3 (사망구간)
		m_pTestAniRenderer->Animation_Create(L"Death_End", L"unit_luxmarid.bmp", 31, 34, false, 0.1f);				// 사망
		m_pTestAniRenderer->Animation_Create(L"Death_Effect", L"unit_luxmarid.bmp", 35, 35, false, 0.1f);				// 사망 이펙트

		m_pTestAniRenderer->Animation_Create(L"BubblePop", L"unit_luxmarid.bmp", 27, 29, false, 0.1f);				// 물풍선 터트리기
		m_pTestAniRenderer->Animation_Create(L"Pop_Effect", L"unit_luxmarid.bmp", 30, 30, false, 0.1f);				// 물풍선 터트릴때 이펙트
		break;
	case Player::Cappy:
		// 렌더
		m_pTestAniRenderer = Create_Renderer<AnimationRenderer>(11);
		m_pTestAniRenderer->Size(F_Position{ 100, 100 });

		m_pTestAniRenderer->Animation_Create(L"UIdle", L"unit_cappy.bmp", 0, 0, true);
		m_pTestAniRenderer->Animation_Create(L"URun", L"unit_cappy.bmp", 1, 5, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"UAttack", L"unit_cappy.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"DIdle", L"unit_cappy.bmp", 5, 5, true);
		m_pTestAniRenderer->Animation_Create(L"DRun", L"unit_cappy.bmp", 6, 10, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"DAttack", L"unit_cappy.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"RIdle", L"unit_cappy.bmp", 15, 15, true);
		m_pTestAniRenderer->Animation_Create(L"RRun", L"unit_cappy.bmp", 16, 20, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"RAttack", L"unit_cappy.bmp", 20, 30, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"LIdle", L"unit_cappy.bmp", 10, 10, true);
		m_pTestAniRenderer->Animation_Create(L"LRun", L"unit_cappy.bmp", 11, 15, true, 0.1f);
		m_pTestAniRenderer->Animation_Create(L"LAttack", L"unit_cappy.bmp", 20, 29, false, 0.2f);

		m_pTestAniRenderer->Animation_Create(L"Death_01", L"unit_cappy.bmp", 20, 26, false, 0.15f);	// 물풍선되기1
		m_pTestAniRenderer->Animation_Create(L"Death_02", L"unit_cappy.bmp", 24, 27, true, 0.15f);	// 물풍선되기2 (반복구간)
		m_pTestAniRenderer->Animation_Create(L"Death_03", L"unit_cappy.bmp", 24, 27, false, 0.15f);	// 물풍선되기3 (사망구간)
		m_pTestAniRenderer->Animation_Create(L"Death_End", L"unit_cappy.bmp", 31, 34, false, 0.1f);				// 사망
		m_pTestAniRenderer->Animation_Create(L"Death_Effect", L"unit_cappy.bmp", 35, 35, false, 0.1f);				// 사망 이펙트

		m_pTestAniRenderer->Animation_Create(L"BubblePop", L"unit_cappy.bmp", 27, 29, false, 0.1f);				// 물풍선 터트리기
		m_pTestAniRenderer->Animation_Create(L"Pop_Effect", L"unit_cappy.bmp", 30, 30, false, 0.1f);				// 물풍선 터트릴때 이펙트
		break;
	case Player::Max:
		break;
	default:
		break;
	}
}



// 아이템 획득 
void Player::Set_UseItem(std::wstring _ItemName, Item::ITEM_TYPE _Type)
{
	std::map<std::wstring, Item*>::iterator Start = m_GetItem.begin();
	std::map<std::wstring, Item*>::iterator End = m_GetItem.end();

	// 기존 아이템이 있을 때
	if (Start != End)
	{
		m_GetItem.clear();			// 삭제
	}

	std::wstring name = _ItemName;
	name += L"_Get";

	// 사용할 수 있는 아이템 추가
	m_GetItem.insert(std::map<std::wstring, Item*>::value_type(name, m_pItem));
	m_pItem->Change_ItemImage(name, _Type);
	m_pItem->ItemState.m_bItem = true;
	int a = 0;  
}

std::wstring Player::UseItem()
{
	std::wstring ItemName = L"";

	if (false == m_pItem->EnabledItem())
		return ItemName;
	
	std::map<std::wstring, Item*>::iterator Item_Iter = m_GetItem.begin();

	if (Item_Iter == m_GetItem.end())
	{
		return ItemName = L"";
	}

	return Item_Iter->first;
}


void Player::Erase_BubbleMap(VECTOR2_INT _Index)
{
	std::map<__int64, Bubble*>::iterator Find_Bubble = m_BubbleMap.find(_Index);

	if (Find_Bubble == m_BubbleMap.end())
	{
		return;
	}

	m_BubbleMap.erase(Find_Bubble);
	--m_CurBubbleCount;
}

void Player::Bubble_Col(ObjectCollision* _Other)
{
	// 물풍선 되기

	if (_Other->Name == L"Bomb")
	{
		m_bIsBubble = true;
		m_pTestAniRenderer->Animation_Change(L"Death_01");
		Player_ChangeState(Death_01, false);
	}
}

void Player::Pos_Init()
{
	F_Position CharPos = m_TileRenderer->OriginTilePos(m_BasePos);
	m_BasePos = CharPos;
}

void Player::Character_PosInit()
{
	// 맵에 따른 캐릭터 초기 위치설정
	if (L"Cookie_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 120, 200 };
	}
	else if (L"Cookie_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 50, 200 };
	}
	else if (L"Desert_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 50, 200 };
	}
	else if (L"Desert_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 50, 100 };
	}
	else if (L"Forest_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 108, 200 };
	}
	else if (L"Forest_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 58, 120 };
	}
	else if (L"Ice_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 58, 200 };
	}
	else if (L"Ice_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 200, 250 };
	}
	else if (L"Pirate_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 57, 117 };
	}
	else if (L"Pirate_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 119, 150 };
	}
	else if (L"Vilage_00" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 50.0f, 50.0f };
	}
	else if (L"Vilage_01" == MainSceneState::SelectMapName)
	{
		m_BasePos = { 50.0f, 50.0f };
	}
}


