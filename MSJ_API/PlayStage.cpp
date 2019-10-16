#include "stdafx.h"
#include "PlayStage.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Monster.h"
#include "MonsterMini.h"
#include "PixelColGround.h"
#include "PlayBackGround.h"
#include "Bubble.h"
#include "EditorTileMap.h"
#include "TileMapRenderer.h"
#include "GameMouseCursor.h"
#include "Item.h"
#include "HPBar.h"
#include "InGameTimer.h"
#include "SoundControl.h"
////////////////////////////////////

PlayStage::PlayStage() : MainSceneState()
{
}


PlayStage::~PlayStage()
{
}

////////////////////////////////////

void PlayStage::Loading()
{
	// 배경음 넣기
	BGM_ON();

	//효과음
	m_SoundControl = ResourceManager::Instance().SoundControl_Insert();
	m_SoundControl->Sound_NewPlay(L"GameStart.ogg");
	m_SoundControl->Sound_SetPitch(1.0f);


	// YSorting
	YSort_On(10);
	YSort_On(11);

	EditorTileMap* pNewTileMap = Create_Actor<EditorTileMap>();
	pNewTileMap->EditorMode_Off();
	pNewTileMap->LoadMap();
	pNewTileMap->EditorTileDelete();
	pNewTileMap->EditorObjDelete();

	// 타이머
	InGameTimer* GameTimer = Create_Actor<InGameTimer>();

	// PixelColGround
	Create_Actor<PixelColGround>();
	Create_Actor<PlayBackGround>();

	// Mouse
	Create_Actor<GameMouseCursor>();

	// 플레이어가 사용할 수 있는 아이템
	Item* p_PlayerItem = Create_Actor<Item>();
	p_PlayerItem->Pos(F_Position{ 0, 0 });

	// 플레이어 생성
	Player* p_Player = Create_Actor<Player>();
	p_Player->m_TileRenderer = pNewTileMap->m_pTileRenderer;		// 타일맵을 알아오기 위해서
	p_Player->m_TileMap = pNewTileMap;								// 타일맵 정보를 알아오기 위해 ( 현재 놓여진 블럭들 정보를 알아오기 위해 )
	p_Player->Pos_Init();
	p_Player->Set_Item(p_PlayerItem);
	p_Player->m_InGameTimer = GameTimer;

	p_PlayerItem->Owner(true);

	MonsterMini* p_MiniMonster = Create_Actor<MonsterMini>();
	p_MiniMonster->m_TileRenderer = pNewTileMap->m_pTileRenderer;
	p_MiniMonster->m_TileMap = pNewTileMap;
	p_MiniMonster->Pos_Init();
	p_MiniMonster->m_InGameTimer = GameTimer;

	Monster* p_Monster = Create_Actor<Monster>();
	p_Monster->m_TileRenderer = pNewTileMap->m_pTileRenderer;
	p_Monster->m_TileMap = pNewTileMap;
	p_Monster->Pos_Init();
	p_Monster->m_InGameTimer = GameTimer;

	//P_MonsterHP->Pos() = p_Monster->Pos();
	Collision_Link(L"Player", L"Item");
	Collision_Link(L"Player", L"Bubble");
	Collision_Link(L"Player_Up", L"Limit_Up");
	Collision_Link(L"Player_Left", L"Limit_Left");
	Collision_Link(L"Player_Right", L"Limit_Right");
	Collision_Link(L"Player_Down", L"Limit_Down");
	Collision_Link(L"Player_Up", L"Bubble");
	Collision_Link(L"Player_Left", L"Bubble");
	Collision_Link(L"Player_Right", L"Bubble");
	Collision_Link(L"Player_Down", L"Bubble");
	Collision_Link(L"Monster", L"PlayerBullet");
	Collision_Link(L"Monster", L"Bubble");
	Collision_Link(L"MiniMonster", L"Bubble");
	Collision_Link(L"Item", L"Bubble");
	Collision_Link(L"InGameExitButton", L"Mouse");

	Collision_Link(L"Bubble", L"Bubble");


}


void PlayStage::Start_Update()
{

}


void PlayStage::End_Debug_Update()
{
}

void PlayStage::LoadMap()
{

}


void PlayStage::BGM_ON()
{
	// 배경음 넣기 (맵에따라서)
	if (L"Cookie_00" == MainSceneState::SelectMapName ||
		L"Cookie_01" == MainSceneState::SelectMapName)
	{
		m_SoundControlBGM->Sound_NewPlay(L"CookieBGM.ogg");
		m_SoundControlBGM->Sound_SetPitch(1.0f);
	}
	else if (L"Desert_00" == MainSceneState::SelectMapName ||
		L"Desert_01" == MainSceneState::SelectMapName)
	{
		m_SoundControlBGM->Sound_NewPlay(L"DesertBGM.ogg");
		m_SoundControlBGM->Sound_SetPitch(1.0f);
	}
	else if (L"Forest_00" == MainSceneState::SelectMapName ||
		L"Forest_01" == MainSceneState::SelectMapName)
	{
		m_SoundControlBGM->Sound_NewPlay(L"ForestBGM.ogg");
		m_SoundControlBGM->Sound_SetPitch(1.0f);
	}
	else if (L"Ice_00" == MainSceneState::SelectMapName ||
		L"Ice_01" == MainSceneState::SelectMapName)
	{
		m_SoundControlBGM->Sound_NewPlay(L"IceBGM.ogg");
		m_SoundControlBGM->Sound_SetPitch(1.0f);
	}
	else if (L"Pirate_00" == MainSceneState::SelectMapName ||
		L"Pirate_01" == MainSceneState::SelectMapName)
	{
		m_SoundControlBGM->Sound_NewPlay(L"PirateBGM.ogg");
		m_SoundControlBGM->Sound_SetPitch(1.0f);
	}
	else if (L"Vilage_00" == MainSceneState::SelectMapName ||
		L"Vilage_01" == MainSceneState::SelectMapName)
	{
		m_SoundControlBGM->Sound_NewPlay(L"VilageBGM.ogg");
		m_SoundControlBGM->Sound_SetPitch(1.0f);
	}
}
