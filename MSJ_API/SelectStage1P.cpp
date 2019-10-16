#include "stdafx.h"
#include "SelectStage1P.h"
#include "Util_Core.h"
#include "ResourceManager.h"
#include "SelectBackground1P.h"
#include "GameMouseCursor.h"
#include "Select_Character1P.h"
#include "SoundControl.h"
#include "MainSceneState.h"




SelectStage1P::SelectStage1P()
{
}


SelectStage1P::~SelectStage1P()
{
}

//////////////////////////////////////

void SelectStage1P::Start_Update()
{
}


void SelectStage1P::End_Debug_Update()
{

}

void SelectStage1P::Loading()
{	
	// 배경음 추가
	m_SoundControlBGM->Sound_NewPlay(L"WaitingRoomBGM.ogg");
	m_SoundControlBGM->Sound_SetPitch(1.0f);

	Create_Actor<SelectBackground1P>();
	GameMouseCursor* MouseCursor = Create_Actor<GameMouseCursor>();
	Select_Character1P* Select_Character = Create_Actor<Select_Character1P>();

	// 캐릭터 선택
	Collision_Link(L"BazziSelect", L"Mouse");
	Collision_Link(L"DaoSelect", L"Mouse");
	Collision_Link(L"MaridSelect", L"Mouse");
	Collision_Link(L"CappySelect", L"Mouse");


	// 맵선택
	Collision_Link(L"MapSelectButton", L"Mouse");
	Collision_Link(L"MapSelectCancle", L"Mouse");

	Collision_Link(L"MapSelectVilage", L"Mouse");
	Collision_Link(L"MapSelectPirate", L"Mouse");
	Collision_Link(L"MapSelectCookie", L"Mouse");
	Collision_Link(L"MapSelectIce", L"Mouse");
	Collision_Link(L"MapSelectForest", L"Mouse");
	Collision_Link(L"MapSelectDesert", L"Mouse");

	Collision_Link(L"MapSelectCheck", L"Mouse");		// 확인
	Collision_Link(L"GameStartButton", L"Mouse");		// 게임시작

}

