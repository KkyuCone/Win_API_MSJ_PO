#include "stdafx.h"
#include "Util_Core.h"
#include "InputManager.h"

#include "PlayStage.h"
#include "TitleStage.h"
#include "EditorStage.h"
#include "SelectStage1P.h"
#include "SelectStage2P.h"

#include "ResourceManager.h"

void Util_Core::UserInit()
{

	// 키 넣기(키 생성, 사용할 수 있는 키 만들기)
	//InputManager::Instance().Create_Key(L"Up", L'W');
	//InputManager::Instance().Create_Key(L"Down", L'S');
	//InputManager::Instance().Create_Key(L"Left", L'A');
	//InputManager::Instance().Create_Key(L"Right", L'D');

	InputManager::Instance().Create_Key(L"Up", VK_UP);
	InputManager::Instance().Create_Key(L"Down", VK_DOWN);
	InputManager::Instance().Create_Key(L"Left", VK_LEFT);
	InputManager::Instance().Create_Key(L"Right", VK_RIGHT);

	InputManager::Instance().Create_Key(L"PrevAni", L'Q');
	InputManager::Instance().Create_Key(L"NextAni", L'E');

	InputManager::Instance().Create_Key(L"PrevTile", L'Q');
	InputManager::Instance().Create_Key(L"NextTile", L'E');

	InputManager::Instance().Create_Key(L"MonsterAttack", L'B');				// 몬스터공격(확인용)

	InputManager::Instance().Create_Key(L"Save", L'T');
	InputManager::Instance().Create_Key(L"Load", L'Y');
	InputManager::Instance().Create_Key(L"EMODECHANGE", L'M');

	InputManager::Instance().Create_Key(L"Ctrl", VK_CONTROL);			// Ctrl

	InputManager::Instance().Create_Key(L"KEY_F12", VK_F10);
	InputManager::Instance().Create_Key(L"KEY_F11", VK_F11);
	InputManager::Instance().Create_Key(L"KEY_F5", VK_F5);

	//InputManager::Instance().Create_Key(L"Bubble", L'B');
	InputManager::Instance().Create_Key(L"Bubble", VK_SPACE);			// 1P 공격키

	InputManager::Instance().Create_Key(L"MouseDown", VK_LBUTTON);
	InputManager::Instance().Create_Key(L"MouseRDown", VK_RBUTTON);
	InputManager::Instance().Create_Key(L"Test", L'J', L'K', L'L');		// 조합키

	// 이미지 경로를 만들고 로드함
	ResourceManager::Instance().RootPath_Create(L"Image");
	ResourceManager::Instance().RootPath_Create(L"MapData");
	ResourceManager::Instance().RootPath_Create(L"Image\\Title");

	ResourceManager::Instance().RootPath_Create(L"Image\\FloorTile");


	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\00ruzzi");		// 오브젝트
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\banifarm");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\camp");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\car");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\cemetery");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\cemetery2");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\cookie");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\desert");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\factory");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\floopy");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\ice");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\pirate");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\sea");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\Vilage");
	ResourceManager::Instance().RootPath_Create(L"Image\\ObjectTile\\zombie");


	ResourceManager::Instance().RootPath_Create(L"Image\\SelectStage");			// 대기방

	ResourceManager::Instance().RootPath_Create(L"Image\\InGame");
	ResourceManager::Instance().RootPath_Create(L"Image\\InGame\\BackGround");
	ResourceManager::Instance().RootPath_Create(L"Image\\InGame\\Bubble");
	ResourceManager::Instance().RootPath_Create(L"Image\\InGame\\Player");
	ResourceManager::Instance().RootPath_Create(L"Image\\InGame\\Monster");
	ResourceManager::Instance().RootPath_Create(L"Image\\InGame\\Item");
	ResourceManager::Instance().RootPath_Create(L"Image\\InGame\\UI");


	ResourceManager::Instance().RootPath_Create(L"Sound\\Effect");
	ResourceManager::Instance().RootPath_Create(L"Sound\\BackGorund");

	// 실제 로드
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\Player", L"unit_bazzi.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\Player", L"PlayerShadow.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\Player", L"unit_dao.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\Player", L"unit_luxmarid.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\Player", L"unit_cappy.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\Bubble", L"bomb_0.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\Bubble", L"bubble_115.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\Bubble", L"bubble_127.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\Bubble", L"bombwater_work.bmp");

	// FadeIn Out Background
	ResourceManager::Instance().LoadToPathImage(L"Image", L"BlackFadeInOut.bmp");

	// 몬스터
	for (size_t i = 1; i < 7; ++i)
	{
		wchar_t ch[256];

		wsprintf(ch, L"Monster_0%d.bmp", i);
		ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\Monster", ch);
	}

	// UI
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\UI", L"HpBack.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\UI", L"HpBar.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\UI", L"Number.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\UI", L"Draw.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\UI", L"Lose.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\UI", L"Start.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\UI", L"Win.bmp");


	// 배경
	ResourceManager::Instance().LoadToPathImage(L"Image", L"BackGround_Col.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\SelectStage", L"SelectBackground_1P.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\SelectStage", L"SelectBackground_2P.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\Title", L"Title_Background.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\BackGround", L"InGame.bmp");

	// 캐릭터 정보, 캐릭터 선택, 맵선택
	ResourceManager::Instance().LoadToPathImage(L"Image\\SelectStage", L"Character_Information.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\SelectStage", L"Character_Select.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\SelectStage", L"MapMainImage.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\SelectStage", L"MapSelectBackground.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\SelectStage", L"MapSelectName.bmp");



	// 버튼
	ResourceManager::Instance().LoadToPathImage(L"Image\\Title", L"TitleButton_1P.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\Title", L"TitleButton_2P.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\Title", L"TitleButton_Editor.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\Title", L"TitleButton_Exit.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\BackGround", L"InGame_ExitButton.bmp");

	// 타일
	ResourceManager::Instance().LoadToPathImage(L"Image\\FloorTile", L"MapFloorTile.bmp");

	// 마우스
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame", L"MouseCursor_None.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\InGame", L"MouseCursor_Click.bmp");

	// 아이템
	for (size_t i = 32; i < 58; ++i)
	{
		wchar_t ch[256];

		wsprintf(ch, L"item_0%d.bmp", i);
		ResourceManager::Instance().LoadToPathImage(L"Image\\InGame\\Item", ch);
	}


	// 오브젝트

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\00ruzzi", L"ruzzi_object_00.bmp");			// 00ruzzi
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\00ruzzi", L"ruzzi_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\00ruzzi", L"ruzzi_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\00ruzzi", L"ruzzi_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\00ruzzi", L"ruzzi_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\00ruzzi", L"ruzzi_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\00ruzzi", L"ruzzi_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\00ruzzi", L"ruzzi_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\00ruzzi", L"ruzzi_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\00ruzzi", L"ruzzi_object_11.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_block_00.bmp");		// baBANIFARM_OBJECT_05DUMMYnifarm
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_block_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_block_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_block_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_block_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_block_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_block_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_block_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_tile_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_tile_16.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_tile_17.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_tile_18.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_tile_19.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_tile_20.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_tile_21.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_tile_22.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\banifarm", L"banifarm_tile_23.bmp");


	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_00.bmp");				// camp
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_block_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_16.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_17.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_18.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_19.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_20.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_21.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\camp", L"camp_object_22.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_block_00.bmp");						// car
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_block_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_16.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_17.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_18.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\car", L"car_object_19.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_block_00.bmp");			// cemetery
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_block_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_block_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_block_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_block_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_block_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_block_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_block_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_16.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_17.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_18.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_19.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_20.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_21.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_22.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_23.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_24.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_25.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_26.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_27.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_28.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_29.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_30.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_31.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_32.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_33.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_34.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_35.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_36.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_37.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_38.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_39.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_40.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_41.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery", L"cemetery_object_42.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_block_00.bmp");			// cemetery2
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_block_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_block_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_block_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_block_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_block_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_16.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_17.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_18.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_19.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_20.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_21.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_22.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_23.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_24.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_25.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_26.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_27.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_28.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_29.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cemetery2", L"cemetery2_object_30.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_block_00.bmp");				// cookie
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_block_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_block_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_block_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_object_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\cookie", L"cookie_tile_03.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_block_00.bmp");				// desert
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_16.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\desert", L"desert_object_17_dummy.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_block_00.bmp");			// factory
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_block_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\factory", L"factory_object_13.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_00.bmp");			// floopy
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_block_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\floopy", L"floopy_object_15.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_block_00.bmp");			// ice
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_16.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_17.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_18.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_19.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_20.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_21.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_22.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_object_23.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_tile_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_tile_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_tile_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_tile_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_tile_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_tile_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_tile_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_tile_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_tile_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_tile_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\ice", L"ice_tile_12.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_block_00.bmp");			// pirate
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_block_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_16.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\pirate", L"pirate_object_17.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_block_sea_block_01.bmp");			// sea
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_block_sea_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_block_sea_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_block_sea_block_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_block_sea_block_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_block_sea_block_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_block_sea_block_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_16.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_17.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_18.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_19.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_20.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_21.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_22.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_23.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_24.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_25.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_26.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_27.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_28.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_29.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_30.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\sea", L"sea_object_31.bmp");

	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_block_00.bmp");			// Vilage
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_block_Move_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"vilage_object_12.bmp");

	// 움직이는 똥상자 ㅡㅡ
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"Nudge_Box_UP.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"Nudge_Box_LEFT.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"Nudge_Box_RIGHT.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\Vilage", L"Nudge_Box_DOWN.bmp");


	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_00.bmp");			// zombie
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_block_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_00.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_01.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_02.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_03.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_04.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_05.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_06.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_07.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_08.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_09.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_10.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_11.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_12.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_13.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_14.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_15.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_16.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_17.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_18.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_19.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_20.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_21.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_22.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_23.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_24.bmp");
	ResourceManager::Instance().LoadToPathImage(L"Image\\ObjectTile\\zombie", L"zombie_object_25.bmp");


	// Editor판
	ResourceManager::Instance().LoadToPathImage(L"Image", L"BlackTilePan.bmp");


	//////////////////////////////////////////////////////////////////////////////////////////////////

	// 이미지 로드 -> 스프라이트 만들기
	ResourceManager::Instance().Sprite_Create(L"BackGround_Col.bmp");
	ResourceManager::Instance().Sprite_Create(L"Title_Background.bmp");			// 타이틀 화면

	ResourceManager::Instance().Sprite_Create(L"TitleButton_1P.bmp");			// 타이틀 버튼
	ResourceManager::Instance().Sprite_Create(L"TitleButton_2P.bmp");
	ResourceManager::Instance().Sprite_Create(L"TitleButton_Editor.bmp");
	ResourceManager::Instance().Sprite_Create(L"TitleButton_Exit.bmp");

	ResourceManager::Instance().Sprite_Create(L"SelectBackground_1P.bmp");		// 선택화면
	ResourceManager::Instance().Sprite_Create(L"SelectBackground_2P.bmp");		

	ResourceManager::Instance().Sprite_Create(L"InGame.bmp");					// 인게임 배경

	ResourceManager::Instance().Sprite_Create(L"MouseCursor_None.bmp");			// 마우스 None
	ResourceManager::Instance().Sprite_Create(L"MouseCursor_Click.bmp");		// 마우스 Click

	ResourceManager::Instance().Sprite_Create(L"HpBack.bmp");		// HP 배경
	ResourceManager::Instance().Sprite_Create(L"HpBar.bmp");		// HP Bar
	//ResourceManager::Instance().Sprite_Create(L"Number.bmp");		// 숫자




	// 이미지 로드 -> (멀티)스프라이트 만들기
	ResourceManager::Instance().MultiSprite_Create(L"unit_bazzi.bmp", { 10, 7});
	ResourceManager::Instance().MultiSprite_Create(L"PlayerShadow.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"unit_dao.bmp", { 10, 7 });
	ResourceManager::Instance().MultiSprite_Create(L"unit_luxmarid.bmp", { 10, 7 });
	ResourceManager::Instance().MultiSprite_Create(L"unit_cappy.bmp", { 10, 7 });
	ResourceManager::Instance().MultiSprite_Create(L"bomb_0.bmp", { 4, 1 });			// 버블
	ResourceManager::Instance().MultiSprite_Create(L"bubble_115.bmp", { 4, 1 });			// 버블
	ResourceManager::Instance().MultiSprite_Create(L"bubble_127.bmp", { 4, 2 });			// 버블
	ResourceManager::Instance().MultiSprite_Create(L"bombwater_work.bmp", { 19, 12 });


	ResourceManager::Instance().MultiSprite_Create(L"MapFloorTile.bmp", { 4, 50 });


	ResourceManager::Instance().MultiSprite_Create(L"BlackTilePan.bmp", { 1, 1 });

	// 숫자 (타이머)
	ResourceManager::Instance().MultiSprite_Create(L"Number.bmp", { 10, 3 });

	// UI 추가 (시작, 승리, 패배, 비김)
	ResourceManager::Instance().MultiSprite_Create(L"Draw.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"Lose.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"Win.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"Start.bmp", { 7, 1 });


	// 인게임 나가기 버튼
	ResourceManager::Instance().MultiSprite_Create(L"InGame_ExitButton.bmp", { 2, 1 });

	// 아이템
	for (size_t i = 32; i < 58; ++i)
	{
		wchar_t ch[256];

		wsprintf(ch, L"item_0%d.bmp", i);
		ResourceManager::Instance().MultiSprite_Create(ch, { 2, 1 });
		int a = 0;
	}

	
	// 이미지 파일 한꺼번에 불러오기
	/*for (size_t i = 0; i < 12; i++)
	{
		wchar_t ch[MAX_PATH];
		if (10 <= i) 
		{	
			wsprintf(ch, L"ruzzi_object_%d.bmp", i);
		}
		else 
		{
			wsprintf(ch, L"ruzzi_object_%d%d.bmp", 0, i);
		}

		GameObjectMultiSprite* pTest =ResourceManager::Instance().MultiSprite_Create(ch, { 2, 1 });
	}*/

	ResourceManager::Instance().MultiSprite_Create(L"ruzzi_object_00.bmp", { 2, 1 });			// 00ruzzi
	ResourceManager::Instance().MultiSprite_Create(L"ruzzi_object_01.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ruzzi_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ruzzi_object_03.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ruzzi_object_04.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ruzzi_object_05.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ruzzi_object_06.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ruzzi_object_09.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ruzzi_object_10.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ruzzi_object_11.bmp", { 1, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"banifarm_block_00.bmp", { 3, 2 });			// banifarm
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_block_01.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_block_02.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_block_03.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_block_04.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_block_05.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_block_06.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_block_07.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_block_08.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_block_09.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_block_10.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_object_00.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_object_04.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_tile_15.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_tile_16.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_tile_17.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_tile_18.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_tile_19.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_tile_20.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_tile_21.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_tile_22.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"banifarm_tile_23.bmp", { 4, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"camp_block_00.bmp", { 3, 2 });			// camp
	ResourceManager::Instance().MultiSprite_Create(L"camp_block_01.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_block_03.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_block_04.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_block_05.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_block_06.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_block_07.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_block_08.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_block_09.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_block_10.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_block_11.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_02.bmp", { 3, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_03.bmp", { 3, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_04.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_05.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_06.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_07.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_08.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_09.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_10.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_11.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_12.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_13.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_14.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_15.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_16.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_17.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_18.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_19.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_20.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_21.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"camp_object_22.bmp", { 1, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"car_block_00.bmp", { 3, 2 });				// car
	ResourceManager::Instance().MultiSprite_Create(L"car_block_01.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"car_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"car_block_03.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"car_block_04.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_04.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_05.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_06.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_07.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_08.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_09.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_10.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_11.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_12.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_13.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_14.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_15.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_16.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_17.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_18.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"car_object_19.bmp", { 2, 3 });

	ResourceManager::Instance().MultiSprite_Create(L"cemetery_block_00.bmp", { 3, 2 });			// cemetery
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_block_01.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_block_03.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_block_04.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_block_05.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_block_06.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_block_07.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_block_08.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_block_09.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_block_10.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_00.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_04.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_05.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_06.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_07.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_08.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_09.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_10.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_11.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_12.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_13.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_14.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_15.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_16.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_17.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_18.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_19.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_20.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_21.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_22.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_23.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_24.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_25.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_26.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_27.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_28.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_29.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_30.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_31.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_32.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_33.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_34.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_35.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_36.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_37.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_38.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_39.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_40.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_41.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery_object_42.bmp", { 3, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_block_00.bmp", { 3, 2 });			// cemetery2
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_block_01.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_block_03.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_block_04.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_block_05.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_block_06.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_block_07.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_block_08.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_03.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_04.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_05.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_06.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_07.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_08.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_09.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_10.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_11.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_12.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_13.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_14.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_15.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_16.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_17.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_18.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_19.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_20.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_21.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_22.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_23.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_24.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_25.bmp", { 3, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_26.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_27.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_28.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_29.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cemetery2_object_30.bmp", { 5, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"cookie_block_00.bmp", { 3, 3 });		// cookie
	ResourceManager::Instance().MultiSprite_Create(L"cookie_block_01.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_block_03.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_block_04.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_block_05.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_block_06.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_04.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_05.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_06.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_07.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_08.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_09.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_10.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_11.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_12.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_13.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_14.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_object_15.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"cookie_tile_03.bmp", { 1, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"desert_block_00.bmp", { 3, 2 });			// desert
	ResourceManager::Instance().MultiSprite_Create(L"desert_block_01.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_block_03.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_04.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_05.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_06.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_07.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_08.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_09.bmp", { 3, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_10.bmp", { 3, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_11.bmp", { 3, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_12.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_13.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_14.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_15.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_16.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"desert_object_17_dummy.bmp", { 1, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"factory_block_00.bmp", { 3, 2 });			// factory
	ResourceManager::Instance().MultiSprite_Create(L"factory_block_01.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_block_03.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_block_04.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_04.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_05.bmp", { 2, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_06.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_07.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_08.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_09.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_10.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_11.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_12.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"factory_object_13.bmp", { 1, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_00.bmp", { 3, 2 });			// floopy
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_01.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_03.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_04.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_05.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_06.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_07.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_08.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_09.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_10.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_11.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_12.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_13.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_14.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_block_15.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_04.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_05.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_06.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_07.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_08.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_09.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_10.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_11.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_12.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_13.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_14.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"floopy_object_15.bmp", { 2, 2 });

	ResourceManager::Instance().MultiSprite_Create(L"ice_block_00.bmp", { 3, 2 });			// ice
	ResourceManager::Instance().MultiSprite_Create(L"ice_block_01.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_block_03.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_04.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_05.bmp", { 3, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_06.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_07.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_08.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_09.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_10.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_11.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_12.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_13.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_14.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_15.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_16.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_17.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_18.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_19.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_20.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_21.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_22.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_object_23.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_tile_02.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_tile_03.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_tile_04.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_tile_05.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_tile_06.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_tile_07.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_tile_08.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_tile_09.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_tile_10.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_tile_11.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"ice_tile_12.bmp", { 2, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"pirate_block_00.bmp", { 3, 2 });			// pirate
	ResourceManager::Instance().MultiSprite_Create(L"pirate_block_01.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_block_03.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_block_04.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_04.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_05.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_06.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_07.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_08.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_09.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_10.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_11.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_12.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_13.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_14.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_15.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_16.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"pirate_object_17.bmp", { 1, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"sea_block_sea_block_01.bmp", { 3, 2 });			// sea
	ResourceManager::Instance().MultiSprite_Create(L"sea_block_sea_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_block_sea_block_03.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_block_sea_block_04.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_block_sea_block_05.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_block_sea_block_06.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_block_sea_block_07.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_04.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_05.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_06.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_07.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_08.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_09.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_10.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_11.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_12.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_13.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_14.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_15.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_16.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_17.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_18.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_19.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_20.bmp", { 3, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_21.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_22.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_23.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_24.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_25.bmp", { 3, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_26.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_27.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_28.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_29.bmp", { 3, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_30.bmp", { 3, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"sea_object_31.bmp", { 1, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"vilage_block_00.bmp", { 3, 3 });		// vilage
	ResourceManager::Instance().MultiSprite_Create(L"vilage_block_01.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"vilage_block_02.bmp", { 3, 3 });
	ResourceManager::Instance().MultiSprite_Create(L"vilage_block_03.bmp", { 6, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"vilage_block_Move_03.bmp", { 6, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"vilage_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"vilage_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"vilage_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"vilage_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"vilage_object_04.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"vilage_object_05.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"vilage_object_12.bmp", { 1, 1 });


	// 움직이는 상자
	ResourceManager::Instance().MultiSprite_Create(L"Nudge_Box_UP.bmp", { 8, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"Nudge_Box_LEFT.bmp", { 10, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"Nudge_Box_RIGHT.bmp", { 10, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"Nudge_Box_DOWN.bmp", { 8, 1 });

	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_00.bmp", { 3, 2 });		// Zombi
	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_01.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_02.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_03.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_04.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_05.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_06.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_07.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_08.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_09.bmp", { 3, 2 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_10.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_block_11.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_00.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_01.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_02.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_03.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_04.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_05.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_06.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_07.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_08.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_09.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_10.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_11.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_12.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_13.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_14.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_15.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_16.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_17.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_18.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_19.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_20.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_21.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_22.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_23.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_24.bmp", { 1, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"zombie_object_25.bmp", { 1, 1 });


	// 필드 몬스터
	ResourceManager::Instance().MultiSprite_Create(L"Monster_01.bmp", { 5, 5 });
	ResourceManager::Instance().MultiSprite_Create(L"Monster_02.bmp", { 5, 5 });
	ResourceManager::Instance().MultiSprite_Create(L"Monster_03.bmp", { 6, 7 });
	ResourceManager::Instance().MultiSprite_Create(L"Monster_04.bmp", { 5, 6 });
	ResourceManager::Instance().MultiSprite_Create(L"Monster_05.bmp", { 5, 6 });
	ResourceManager::Instance().MultiSprite_Create(L"Monster_06.bmp", { 6, 8 });

	// 선택화면 - 캐릭터 정보, 캐릭터 선택, 맵선택
	ResourceManager::Instance().MultiSprite_Create(L"Character_Information.bmp", { 5, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"Character_Select.bmp", { 4, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"MapMainImage.bmp", { 7, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"MapSelectBackground.bmp", { 2, 1 });
	ResourceManager::Instance().MultiSprite_Create(L"MapSelectName.bmp", { 1, 13 });

	// FadeInOut
	ResourceManager::Instance().MultiSprite_Create(L"BlackFadeInOut.bmp", { 1, 1 });



	// Sound
	// BGM -  반복재생
	ResourceManager::Instance().SoundBGM_Load(L"Sound\\BackGorund", L"BossBGM.ogg");
	ResourceManager::Instance().SoundBGM_Load(L"Sound\\BackGorund", L"CookieBGM.ogg");
	ResourceManager::Instance().SoundBGM_Load(L"Sound\\BackGorund", L"GhostBGM.ogg");
	ResourceManager::Instance().SoundBGM_Load(L"Sound\\BackGorund", L"IceBGM.ogg");
	ResourceManager::Instance().SoundBGM_Load(L"Sound\\BackGorund", L"MainSceneBGM.ogg");
	ResourceManager::Instance().SoundBGM_Load(L"Sound\\BackGorund", L"WaitingRoomBGM.ogg");
	ResourceManager::Instance().SoundBGM_Load(L"Sound\\BackGorund", L"DesertBGM.ogg");
	ResourceManager::Instance().SoundBGM_Load(L"Sound\\BackGorund", L"FactoryBGM.ogg");
	ResourceManager::Instance().SoundBGM_Load(L"Sound\\BackGorund", L"ForestBGM.ogg");
	ResourceManager::Instance().SoundBGM_Load(L"Sound\\BackGorund", L"PirateBGM.ogg");
	ResourceManager::Instance().SoundBGM_Load(L"Sound\\BackGorund", L"VilageBGM.ogg");

	// Effect
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"BubbleBomb.ogg");
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"BubbleInstall.ogg");
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"BubbleSave.ogg");
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"Coin.ogg");
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"EatItem_00.ogg");
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"EatItem_01.ogg");
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"GameStart.ogg");
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"HurryUp.ogg");
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"Lose.ogg");
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"Win.ogg");
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"ButtonClick.ogg");
	ResourceManager::Instance().Sound_Load(L"Sound\\Effect", L"Draw.ogg");






	Create_Stage<TitleStage>(ALLSTAGE::TITLE);
	Create_Stage<SelectStage1P>(ALLSTAGE::GAMESELECT);
	Create_Stage<SelectStage2P>(ALLSTAGE::GAMESELECT_2P);
	Create_Stage<PlayStage>(ALLSTAGE::PLAY);
	//Create_Stage<TitleStage>(ALLSTAGE::PLAY_2P);
	Create_Stage<EditorStage>(ALLSTAGE::EDITOR);
	ChangeStage(ALLSTAGE::TITLE);

}