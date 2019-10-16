#include "stdafx.h"
#include "EditorTileMap.h"
#include "SingleRenderer.h"
#include "BinaryWriteStream.h"
#include "BinaryReadStream.h"
#include "ResourceManager.h"
#include "ObjectCollision.h"
#include "EditorStage.h"
#include "ObjTile.h"
#include "Item.h"
#include "AnimationRenderer.h"
#include "RenderManager.h"
#include <Windows.h>
#include "Util_Core.h"
#include "resource.h"
#include "MainSceneState.h"

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

wchar_t FileName[1000];

////////////////////////////////////////////////////
EditorTileMap::EditorTileMap()
	: m_pTileCol(nullptr), m_TileTime(0.0f), m_FadeTimer(1.0f), eMode(EDITORMODE::TILE),
	m_bEditorMode(true)
{
}


EditorTileMap::~EditorTileMap()
{
}
////////////////////////////////////////////////////

void EditorTileMap::Start_Update()
{
	if (true == m_bEditorMode)
	{
		m_BlackTileIndex = 0;
		m_TileIndex = 80;		// 선택된 타일 
		m_ObjectIndex = DESERT_OBJECT_17_DUMMY;

		// 선택된 타일 보여주기(이미지)
		m_pSelectTile = Create_Renderer<SingleRenderer>(8);
		m_pSelectTile->CameraMode(false);
		m_pSelectTile->SettingSprite(L"MapFloorTile.bmp", m_TileIndex);
		m_pSelectTile->Pivot(F_Position{ 920, 150 });
		m_pSelectTile->Size(F_Position{ 100, 100 });

		m_pSelectObj = Create_Renderer<SingleRenderer>(8);
		m_pSelectObj->CameraMode(false);
		m_pSelectObj->SettingSprite(L"ruzzi_object_00.bmp", 0);			// ruzzi_object_00
		m_pSelectObj->Pivot(F_Position{ 920, 400 });
		m_pSelectObj->Size(F_Position{ 100, 100 });


		// 실제 타일 + 오브젝트

		m_pBlackTile = Create_Renderer<TileMapRenderer>(8);
		m_pBlackTile->Create_MapTile(L"BlackTilePan.bmp", { 54, 55 });
		m_pBlackTile->Pivot({ 30, 54 });

		m_pTileRenderer = Create_Renderer<TileMapRenderer>(8);
		m_pTileRenderer->Create_MapTile(L"MapFloorTile.bmp", { 54, 55 });
		m_pTileRenderer->Pivot({ 30, 54 });

		// 블럭들 렌더
		m_pObjRenderer = Create_Renderer<AnimationRenderer>(10);
		m_pObjRenderer->Size(F_Position{ 58, 40.5f });

		m_pObjRenderer->Animation_Create(L"ruzzi_object_00", L"ruzzi_object_00.bmp", 0, 1, true, 0.1f);
	}
}

// 선택된 블럭 이미지 보여주기용
void EditorTileMap::ObjectSelect(OBJTYPE _ObjType)
{

	switch (_ObjType)
	{
	case EditorTileMap::RUZZI_OBJECT_00:							// ruzzi
	{
		m_pSelectObj->SettingSprite(L"ruzzi_object_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });

		break;
	}
	case EditorTileMap::RUZZI_OBJECT_01:
	{
		m_pSelectObj->SettingSprite(L"ruzzi_object_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::RUZZI_OBJECT_02:
	{
		m_pSelectObj->SettingSprite(L"ruzzi_object_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::RUZZI_OBJECT_03:
	{
		m_pSelectObj->SettingSprite(L"ruzzi_object_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::RUZZI_OBJECT_04:
	{
		m_pSelectObj->SettingSprite(L"ruzzi_object_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::RUZZI_OBJECT_05:
	{
		m_pSelectObj->SettingSprite(L"ruzzi_object_05.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::RUZZI_OBJECT_06:
	{
		m_pSelectObj->SettingSprite(L"ruzzi_object_06.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::RUZZI_OBJECT_09:
	{
		m_pSelectObj->SettingSprite(L"ruzzi_object_09.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::RUZZI_OBJECT_10:
	{
		m_pSelectObj->SettingSprite(L"ruzzi_object_10.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::RUZZI_OBJECT_11:
	{
		m_pSelectObj->SettingSprite(L"ruzzi_object_11.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_BLOCK_00:										// banifarm
	{
		m_pSelectObj->SettingSprite(L"banifarm_block_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_BLOCK_01:
	{
		m_pSelectObj->SettingSprite(L"banifarm_block_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_BLOCK_02:
	{
		m_pSelectObj->SettingSprite(L"banifarm_block_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_BLOCK_03:
	{
		m_pSelectObj->SettingSprite(L"banifarm_block_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_BLOCK_04:
	{
		m_pSelectObj->SettingSprite(L"banifarm_block_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_BLOCK_05:
	{
		m_pSelectObj->SettingSprite(L"banifarm_block_05.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_BLOCK_06:
	{
		m_pSelectObj->SettingSprite(L"banifarm_block_06.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_BLOCK_07:
	{
		m_pSelectObj->SettingSprite(L"banifarm_block_07.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_BLOCK_08:
	{
		m_pSelectObj->SettingSprite(L"banifarm_block_08.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_BLOCK_09:
	{
		m_pSelectObj->SettingSprite(L"banifarm_block_09.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_BLOCK_10:
	{
		m_pSelectObj->SettingSprite(L"banifarm_block_10.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_OBJECT_00:
	{
		m_pSelectObj->SettingSprite(L"banifarm_object_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_OBJECT_02:
	{
		m_pSelectObj->SettingSprite(L"banifarm_object_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_OBJECT_03:
	{
		m_pSelectObj->SettingSprite(L"banifarm_object_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_OBJECT_04:
	{
		m_pSelectObj->SettingSprite(L"banifarm_object_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_TILE_15:
	{
		m_pSelectObj->SettingSprite(L"banifarm_tile_15.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_TILE_16:
	{
		m_pSelectObj->SettingSprite(L"banifarm_tile_16.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_TILE_17:
	{
		m_pSelectObj->SettingSprite(L"banifarm_tile_17.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_TILE_18:
	{
		m_pSelectObj->SettingSprite(L"banifarm_tile_18.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_TILE_19:
	{
		m_pSelectObj->SettingSprite(L"banifarm_tile_19.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_TILE_20:
	{
		m_pSelectObj->SettingSprite(L"banifarm_tile_20.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_TILE_21:
	{
		m_pSelectObj->SettingSprite(L"banifarm_tile_21.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_TILE_22:
	{
		m_pSelectObj->SettingSprite(L"banifarm_tile_22.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::BANIFARM_TILE_23:
	{
		m_pSelectObj->SettingSprite(L"banifarm_tile_23.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}


	case EditorTileMap::CAMP_BLOCK_00:							// camp
	{
		m_pSelectObj->SettingSprite(L"camp_block_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_01:
	{
		m_pSelectObj->SettingSprite(L"camp_block_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_02:
	{
		m_pSelectObj->SettingSprite(L"camp_block_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_03:
	{
		m_pSelectObj->SettingSprite(L"camp_block_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_04:
	{
		m_pSelectObj->SettingSprite(L"camp_block_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_05:
	{
		m_pSelectObj->SettingSprite(L"camp_block_05.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_06:
	{
		m_pSelectObj->SettingSprite(L"camp_block_06.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_07:
	{
		m_pSelectObj->SettingSprite(L"camp_block_07.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_08:
	{
		m_pSelectObj->SettingSprite(L"camp_block_08.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_09:
	{
		m_pSelectObj->SettingSprite(L"camp_block_09.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_10:
	{
		m_pSelectObj->SettingSprite(L"camp_block_10.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_11:
	{
		m_pSelectObj->SettingSprite(L"camp_block_11.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_00:
	{
		m_pSelectObj->SettingSprite(L"camp_object_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_01:
	{
		m_pSelectObj->SettingSprite(L"camp_object_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_02:
	{
		m_pSelectObj->SettingSprite(L"camp_object_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_03:
	{
		m_pSelectObj->SettingSprite(L"camp_object_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_04:
	{
		m_pSelectObj->SettingSprite(L"camp_object_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_05:
	{
		m_pSelectObj->SettingSprite(L"camp_object_05.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_06:
	{
		m_pSelectObj->SettingSprite(L"camp_object_06.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_07:
	{
		m_pSelectObj->SettingSprite(L"camp_object_07.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_08:
	{
		m_pSelectObj->SettingSprite(L"camp_object_08.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_09:
	{
		m_pSelectObj->SettingSprite(L"camp_object_09.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_10:
	{
		m_pSelectObj->SettingSprite(L"camp_object_10.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_11:
	{
		m_pSelectObj->SettingSprite(L"camp_object_11.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_12:
	{
		m_pSelectObj->SettingSprite(L"camp_object_12.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_13:
	{
		m_pSelectObj->SettingSprite(L"camp_object_13.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_14:
	{
		m_pSelectObj->SettingSprite(L"camp_object_14.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_15:
	{
		m_pSelectObj->SettingSprite(L"camp_object_15.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_16:
	{
		m_pSelectObj->SettingSprite(L"camp_object_16.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_17:
	{
		m_pSelectObj->SettingSprite(L"camp_object_17.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_18:
	{
		m_pSelectObj->SettingSprite(L"camp_object_18.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_19:
	{
		m_pSelectObj->SettingSprite(L"camp_object_19.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_20:
	{
		m_pSelectObj->SettingSprite(L"camp_object_20.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_21:
	{
		m_pSelectObj->SettingSprite(L"camp_object_21.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_22:
	{
		m_pSelectObj->SettingSprite(L"camp_object_22.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_BLOCK_00:						// cookie
	{
		m_pSelectObj->SettingSprite(L"cookie_block_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_BLOCK_01:
	{
		m_pSelectObj->SettingSprite(L"cookie_block_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_BLOCK_02:
	{
		m_pSelectObj->SettingSprite(L"cookie_block_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_BLOCK_03:
	{
		m_pSelectObj->SettingSprite(L"cookie_block_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_BLOCK_04:
	{
		m_pSelectObj->SettingSprite(L"cookie_block_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_BLOCK_05:
	{
		m_pSelectObj->SettingSprite(L"cookie_block_05.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_BLOCK_06:
	{
		m_pSelectObj->SettingSprite(L"cookie_block_06.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_00:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_01:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_02:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_03:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_04:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_05:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_05.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_06:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_06.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_07:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_07.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_08:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_08.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_09:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_09.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_10:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_10.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_11:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_11.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_12:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_12.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_13:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_13.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_14:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_14.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_15:
	{
		m_pSelectObj->SettingSprite(L"cookie_object_15.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::COOKIE_TILE_03:
	{
		m_pSelectObj->SettingSprite(L"cookie_tile_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}

	// desert ~ sea

	case EditorTileMap::DESERT_BLOCK_00:							// desert
	{
		m_pSelectObj->SettingSprite(L"desert_block_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_BLOCK_01:
	{
		m_pSelectObj->SettingSprite(L"desert_block_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_BLOCK_02:
	{
		m_pSelectObj->SettingSprite(L"desert_block_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_BLOCK_03:
	{
		m_pSelectObj->SettingSprite(L"desert_block_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_00:
	{
		m_pSelectObj->SettingSprite(L"desert_object_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_01:
	{
		m_pSelectObj->SettingSprite(L"desert_object_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_02:
	{
		m_pSelectObj->SettingSprite(L"desert_object_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_03:
	{
		m_pSelectObj->SettingSprite(L"desert_object_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_04:
	{
		m_pSelectObj->SettingSprite(L"desert_object_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_05:
	{
		m_pSelectObj->SettingSprite(L"desert_object_05.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_06:
	{
		m_pSelectObj->SettingSprite(L"desert_object_06.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_07:
	{
		m_pSelectObj->SettingSprite(L"desert_object_07.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_08:
	{
		m_pSelectObj->SettingSprite(L"desert_object_08.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_09:
	{
		m_pSelectObj->SettingSprite(L"desert_object_09.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_10:
	{
		m_pSelectObj->SettingSprite(L"desert_object_10.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_11:
	{
		m_pSelectObj->SettingSprite(L"desert_object_11.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_12:
	{
		m_pSelectObj->SettingSprite(L"desert_object_12.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_13:
	{
		m_pSelectObj->SettingSprite(L"desert_object_13.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_14:
	{
		m_pSelectObj->SettingSprite(L"desert_object_14.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_15:
	{
		m_pSelectObj->SettingSprite(L"desert_object_15.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_16:
	{
		m_pSelectObj->SettingSprite(L"desert_object_16.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_17_DUMMY:
	{
		m_pSelectObj->SettingSprite(L"desert_object_17_dummy.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_BLOCK_00:				//ice
	{
		m_pSelectObj->SettingSprite(L"ice_block_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_BLOCK_01:
	{
		m_pSelectObj->SettingSprite(L"ice_block_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_BLOCK_02:
	{
		m_pSelectObj->SettingSprite(L"ice_block_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_BLOCK_03:
	{
		m_pSelectObj->SettingSprite(L"ice_block_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_00:
	{
		m_pSelectObj->SettingSprite(L"ice_object_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_01:
	{
		m_pSelectObj->SettingSprite(L"ice_object_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_02:
	{
		m_pSelectObj->SettingSprite(L"ice_object_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_03:
	{
		m_pSelectObj->SettingSprite(L"ice_object_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_04:
	{
		m_pSelectObj->SettingSprite(L"ice_object_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_05:
	{
		m_pSelectObj->SettingSprite(L"ice_object_05.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_06:
	{
		m_pSelectObj->SettingSprite(L"ice_object_06.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_07:
	{
		m_pSelectObj->SettingSprite(L"ice_object_07.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_08:
	{
		m_pSelectObj->SettingSprite(L"ice_object_08.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_09:
	{
		m_pSelectObj->SettingSprite(L"ice_object_09.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_10:
	{
		m_pSelectObj->SettingSprite(L"ice_object_10.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_11:
	{
		m_pSelectObj->SettingSprite(L"ice_object_11.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_12:
	{
		m_pSelectObj->SettingSprite(L"ice_object_12.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_13:
	{
		m_pSelectObj->SettingSprite(L"ice_object_13.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_14:
	{
		m_pSelectObj->SettingSprite(L"ice_object_14.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_15:
	{
		m_pSelectObj->SettingSprite(L"ice_object_15.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_16:
	{
		m_pSelectObj->SettingSprite(L"ice_object_16.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_17:
	{
		m_pSelectObj->SettingSprite(L"ice_object_17.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_18:
	{
		m_pSelectObj->SettingSprite(L"ice_object_18.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_19:
	{
		m_pSelectObj->SettingSprite(L"ice_object_19.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_20:
	{
		m_pSelectObj->SettingSprite(L"ice_object_20.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_21:
	{
		m_pSelectObj->SettingSprite(L"ice_object_21.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_22:
	{
		m_pSelectObj->SettingSprite(L"ice_object_22.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_23:
	{
		m_pSelectObj->SettingSprite(L"ice_object_23.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_TILE_02:
	{
		m_pSelectObj->SettingSprite(L"ice_tile_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_TILE_03:
	{
		m_pSelectObj->SettingSprite(L"ice_tile_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_TILE_04:
	{
		m_pSelectObj->SettingSprite(L"ice_tile_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_TILE_05:
	{
		m_pSelectObj->SettingSprite(L"ice_tile_05.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_TILE_06:
	{
		m_pSelectObj->SettingSprite(L"ice_tile_06.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_TILE_07:
	{
		m_pSelectObj->SettingSprite(L"ice_tile_07.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_TILE_08:
	{
		m_pSelectObj->SettingSprite(L"ice_tile_08.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_TILE_09:
	{
		m_pSelectObj->SettingSprite(L"ice_tile_09.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_TILE_10:
	{
		m_pSelectObj->SettingSprite(L"ice_tile_10.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_TILE_11:
	{
		m_pSelectObj->SettingSprite(L"ice_tile_11.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::ICE_TILE_12:
	{
		m_pSelectObj->SettingSprite(L"ice_tile_12.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}

	case EditorTileMap::PIRATE_BLOCK_00:						// pirate
	{
		m_pSelectObj->SettingSprite(L"pirate_block_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_01:
	{
		m_pSelectObj->SettingSprite(L"pirate_block_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_02:
	{
		m_pSelectObj->SettingSprite(L"pirate_block_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_03:
	{
		m_pSelectObj->SettingSprite(L"pirate_block_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_04:
	{
		m_pSelectObj->SettingSprite(L"pirate_block_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_00:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_01:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_02:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_03:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_04:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_05:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_05.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_06:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_06.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_07:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_07.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_08:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_08.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_09:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_09.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_10:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_10.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_11:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_11.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_12:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_12.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_13:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_13.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_14:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_14.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_15:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_15.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_16:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_16.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_17:
	{
		m_pSelectObj->SettingSprite(L"pirate_object_17.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::VILAGE_BLOCK_00:							// vilage
	{
		m_pSelectObj->SettingSprite(L"vilage_block_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::VILAGE_BLOCK_01:
	{
		m_pSelectObj->SettingSprite(L"vilage_block_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::VILAGE_BLOCK_02:
	{
		m_pSelectObj->SettingSprite(L"vilage_block_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::VILAGE_BLOCK_03:
	{
		m_pSelectObj->SettingSprite(L"vilage_block_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::VILAGE_OBJECT_00:
	{
		m_pSelectObj->SettingSprite(L"vilage_object_00.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::VILAGE_OBJECT_01:
	{
		m_pSelectObj->SettingSprite(L"vilage_object_01.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::VILAGE_OBJECT_02:
	{
		m_pSelectObj->SettingSprite(L"vilage_object_02.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::VILAGE_OBJECT_03:
	{
		m_pSelectObj->SettingSprite(L"vilage_object_03.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::VILAGE_OBJECT_04:
	{
		m_pSelectObj->SettingSprite(L"vilage_object_04.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::VILAGE_OBJECT_05:
	{
		m_pSelectObj->SettingSprite(L"vilage_object_05.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::VILAGE_OBJECT_12:
	{
		m_pSelectObj->SettingSprite(L"vilage_object_12.bmp", 0);
		m_pSelectObj->Size(F_Position{ 100, 100 });
		break;
	}
	case EditorTileMap::OBJTYPE_MAX:				// MAX
	{
		break;
	}
	default:
		break;
	}
}

void EditorTileMap::Prev_Update()
{
}

void EditorTileMap::Update()
{
	if (false == EditorStage::IsStart())
	{
		return;
	}

	if (false == m_bEditorMode)
	{
		return;
	}

	// 이전 타일, 다음 타일
	if (true == InputManager::Instance().Down(L"PrevTile"))
	{
		switch (eMode)
		{
		case EditorTileMap::OBJ:
			Obj_Prev();
			break;
		case EditorTileMap::TILE:
			Tile_Prev();
			break;
		default:
			break;
		}
	}

	if (true == InputManager::Instance().Down(L"NextTile"))
	{
		switch (eMode)
		{
		case EditorTileMap::OBJ:
			Obj_Next();
			break;
		case EditorTileMap::TILE:
			Tile_Next();
			break;
		default:
			break;
		}

	}


	// 저장, 불러오기
	if (true == InputManager::Instance().DownStay(L"Save"))
	{
		// 다이얼로그를 띄워준다.
		SaveMap();
	}


	if (true == InputManager::Instance().DownStay(L"Load"))
	{
		// 다이얼로그를 띄워준다.
		LoadMap();
	}

	if (true == InputManager::Instance().Down(L"EMODECHANGE"))
	{
		if (eMode == EDITORMODE::TILE)
		{
			eMode = EDITORMODE::OBJ;
		}
		else
		{
			eMode = EDITORMODE::TILE;
		}
	}

	switch (eMode)
	{
	case EditorTileMap::OBJ:
		ObjUpdate();
		break;
	case EditorTileMap::TILE:
		TileUpdate();
		break;
	default:
		break;
	}
}

void EditorTileMap::Tile_Prev()
{
	--m_TileIndex;

	if (m_TileIndex <= 0)
	{
		m_TileIndex = m_pTileRenderer->Get_SpriteCount() - 1;
	}

	m_pSelectTile->SettingSprite(L"MapFloorTile.bmp", m_TileIndex);
}

void EditorTileMap::Tile_Next()
{
	++m_TileIndex;

	if (m_TileIndex >= (int)m_pTileRenderer->Get_SpriteCount())
	{
		m_TileIndex = 0;
	}

	// 다음 타일 선택
	m_pSelectTile->SettingSprite(L"MapFloorTile.bmp", m_TileIndex);
}

// 이전 오브젝트 
void EditorTileMap::Obj_Prev()
{
	--m_ObjectIndex;

	if (m_ObjectIndex < 0)
	{
		m_ObjectIndex = 0;
	}

	ObjectSelect((OBJTYPE)m_ObjectIndex);

}

// 다음 오브젝트 
void EditorTileMap::Obj_Next()
{
	++m_ObjectIndex;

	if (m_ObjectIndex >= OBJTYPE_MAX)
	{
		m_ObjectIndex = (OBJTYPE_MAX - 1);
	}

	ObjectSelect((OBJTYPE)m_ObjectIndex);
}

void EditorTileMap::TileUpdate() {

	if (false == m_bEditorMode)
		return;

	// 타일넣기
	if (true == InputManager::Instance().DownStay(L"MouseDown"))
	{
		m_pTileRenderer->Set_ScreenPosTile(InputManager::Instance().MousePos_F(), m_TileIndex);
	}

	// 타일 지우기
	if (true == InputManager::Instance().DownStay(L"MouseRDown"))
	{
		m_pTileRenderer->Erase_ScreenPosTile(InputManager::Instance().MousePos_F());
	}
}

// 블럭 추가, 삭제
void EditorTileMap::ObjUpdate() {

	if (false == m_bEditorMode)
		return;

	// 블럭 놓기
	if (true == InputManager::Instance().DownStay(L"MouseDown"))
	{
		F_Position Pos = m_pTileRenderer->OriginTilePos(InputManager::Instance().MousePos_F());

		// 다른 블럭이 있는지 추가체크
		if (false == AddObjPosCheck((OBJTYPE)m_ObjectIndex, Pos))
		{
			return;
		}

		// 블럭 추가
		CreateObjIndex((OBJTYPE)m_ObjectIndex, Pos);
	}

	// 블럭 지우기
	if (true == InputManager::Instance().DownStay(L"MouseRDown"))
	{
		F_Position Pos = m_pTileRenderer->OriginTilePos(InputManager::Instance().MousePos_F());
		Erase_ObjIndex(Pos);
	}
}


bool EditorTileMap::AddObjPosCheck(OBJTYPE _ObjType, F_Position _ClickPos)
{
	VECTOR2_INT AddTileIndex = VECTOR2_INT{ 0, 0 };
	F_Position AddTilePos = F_Position{ 0,0 };
	TileMapRenderer::Tile* pAddTile = nullptr;

	switch (_ObjType)
	{
	case EditorTileMap::BANIFARM_OBJECT_00:			// 물웅덩이
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				int a = 0;
				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}
				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		return true;
		break;
	}
	case EditorTileMap::BANIFARM_OBJECT_02:			// 집
	{

		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 4; x++)
			{
				int a = 0;
				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}
				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		return true;
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_09:			// 딸기 케이크
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		return true;
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_10:			// 블루베리 케이크
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_11:			// 달콤한 왕배찌
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 4; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_12:			// 너구리 케이크
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_13:			// 커피
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_14:			// 왕도넛
	{
		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_15:			// 왕도넛 2층
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	case EditorTileMap::DESERT_OBJECT_04:			// 야자수 + 물
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	case EditorTileMap::ICE_OBJECT_04:				// 빨간 지붕 집
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	case EditorTileMap::ICE_OBJECT_05:				// 나무집
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	case EditorTileMap::ICE_OBJECT_06:				// 이글루
	{
		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 3; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_05:			// 깃발
	{
		int a = 0;
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 3; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);
				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}

		break;
	}
	case EditorTileMap::VILAGE_OBJECT_04:			// 풍차
	{
		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 3; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);
				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	case EditorTileMap::VILAGE_OBJECT_12:			// 비행기
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					return false;
				}

				if (pAddTile->ObjIndex > -1)
				{
					return false;
				}
			}
		}
		break;
	}
	default:
		AddTileIndex = m_pTileRenderer->OriginTileIndex(_ClickPos);
		AddTileIndex = (VECTOR2_INT)AddTileIndex;
		AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

		pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

		if (pAddTile == nullptr)
		{
			return false;
		}

		if (pAddTile->ObjIndex > -1)
		{
			return false;
		}
		break;
	}

	return true;
}

void EditorTileMap::Late_Update()
{
	Rectangle(BHDC, 0, 0, 1024, 768);
}

// 맵 불러오기
void EditorTileMap::LoadMap()
{
	m_pTileRenderer->Reset();

	std::wstring Path = ResourceManager::Instance().FindPath(L"MapData");
	//Path += L"MDATA.MD";
	//Path += FileName;
	//Path += L".MD";

	if (true == m_bEditorMode)
	{
		DialogBox(Util_Core::Instance().WINDOW_INSTANCE(), MAKEINTRESOURCE(IDD_LOAD), Util_Core::Instance().WINDOW_HWND(), DlgProc);
		Path += FileName;
	}
	else
	{
		//Path += L"Vilage_01";
		//Path += L"Vilage_01";

		if (L"" == MainSceneState::SelectMapName)
		{
			Path += L"Ice_00";
		}
		else
		{
			Path += MainSceneState::SelectMapName;
		}
	}


	Path += L".MD";


	BinaryReadStream binaryRead = BinaryReadStream(Path.c_str());

	size_t AllCount = 0;

	binaryRead.Binary_Read(&AllCount, sizeof(size_t), sizeof(size_t));
	TileMapRenderer::OutPutTile* AllTile = new TileMapRenderer::OutPutTile[AllCount];


	binaryRead.Binary_Read(AllTile, sizeof(TileMapRenderer::OutPutTile) * AllCount, sizeof(TileMapRenderer::OutPutTile) * AllCount);


	for (size_t i = 0; i < AllCount; ++i)
	{
		TileMapRenderer::OutPutTile OutputTile = AllTile[i];
		m_pTileRenderer->SetTile(AllTile[i].Index, AllTile[i].TileData.TileImageIndex);

		// 블럭
		if (-1 != AllTile[i].TileData.ObjIndex)
		{
			F_Position Pos = m_pTileRenderer->OriginTilePos(AllTile[i].Index);
			CreateObjIndex((OBJTYPE)AllTile[i].TileData.ObjIndex, Pos);
			int a = 0;
		}

		// 아이템 
		if (0 < AllTile[i].TileData.ItemType)
		{
			F_Position Pos = m_pTileRenderer->OriginTilePos(AllTile[i].Index);
			Open_ItemData(AllTile[i].TileData.ItemType, Pos);
			int a = 0;
		}
	}

	delete[] AllTile;
}

// 맵 저장
void EditorTileMap::SaveMap()
{
	DialogBox(Util_Core::Instance().WINDOW_INSTANCE(), MAKEINTRESOURCE(IDD_SAVE), Util_Core::Instance().WINDOW_HWND(), DlgProc);

	// 바닥 타일
	TileMapRenderer::OutPutTile* AllTileData = new TileMapRenderer::OutPutTile[m_pTileRenderer->Get_TileCount()];
	m_pTileRenderer->Get_TileData(AllTileData, m_pTileRenderer->Get_TileCount());

	std::wstring Path = ResourceManager::Instance().FindPath(L"MapData");
	Path += FileName;
	Path += L".MD";

	BinaryWriteStream binaryWrite = BinaryWriteStream(Path.c_str());
	size_t AllCount = m_pTileRenderer->Get_TileCount();

	binaryWrite.Binary_Wirte(&AllCount, sizeof(size_t));
	binaryWrite.Binary_Wirte(AllTileData, sizeof(TileMapRenderer::OutPutTile) * m_pTileRenderer->Get_TileCount());
	delete[] AllTileData;
}


void EditorTileMap::EditorTileDelete()
{
	m_pSelectTile->Obj_Death();
}

void EditorTileMap::EditorObjDelete()
{
	m_pSelectObj->Obj_Death();
}

// DebugRender
void EditorTileMap::DebugRender()
{
	if (false == m_bEditorMode)
	{
		return;
	}


	wchar_t OutText[100];

	switch (eMode)
	{
	case EditorTileMap::OBJ:
		swprintf_s(OutText, L"OBJ");
		break;
	case EditorTileMap::TILE:
		swprintf_s(OutText, L"TILE");
		break;
	default:
		break;
	}

	TextOutW(BHDC, 800, 500, OutText, lstrlenW(OutText));
	VECTOR2_INT PositionIndex = m_pTileRenderer->OriginTileIndex(InputManager::Instance().MousePos_F());
	swprintf_s(OutText, L"X : %d Y : %d", PositionIndex.X, PositionIndex.Y);
	TextOutW(BHDC, 800, 520, OutText, lstrlenW(OutText));
}

// 블럭같은거 생성
ActorObjBase* EditorTileMap::CreateObjIndex(OBJTYPE _Index, F_Position _Pos)
{
	int a = 0;
	VECTOR2_INT Index = m_pTileRenderer->OriginTileIndex(_Pos);

	if (Index.X < 0 || Index.Y < 0)
	{
		return nullptr;
	}

	std::map<__int64, ActorObjBase*>::iterator Find_Iter = m_ObjTile.find(Index);


	if (Find_Iter != m_ObjTile.end())
	{
		return nullptr;
	}

	ActorObjBase* Obj = nullptr;
	AnimationRenderer* pRender = nullptr;


	switch (_Index)
	{
	case EditorTileMap::RUZZI_OBJECT_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ruzzi_object_00", L"ruzzi_object_00.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ruzzi_object_00");
		pRender->Size({ 63, 75 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::RUZZI_OBJECT_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ruzzi_object_01", L"ruzzi_object_01.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ruzzi_object_01");
		pRender->Size({ 56, 75 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::RUZZI_OBJECT_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ruzzi_object_02", L"ruzzi_object_02.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"ruzzi_object_02");
		pRender->Size({ 57, 75 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::RUZZI_OBJECT_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ruzzi_object_03", L"ruzzi_object_03.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ruzzi_object_03");
		pRender->Size({ 61, 128 });
		pRender->Pivot({ -1.0f, -35.0f });
		break;

	}
	case EditorTileMap::RUZZI_OBJECT_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ruzzi_object_04", L"ruzzi_object_04.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ruzzi_object_04");
		pRender->Size({ 61, 75 });
		pRender->Pivot({ -1.5f, -10.0f });
		break;

	}
	case EditorTileMap::RUZZI_OBJECT_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ruzzi_object_05", L"ruzzi_object_05.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ruzzi_object_05");
		pRender->Size({ 60, 75 });
		pRender->Pivot({ -1.0f, -9.0f });
		break;

	}
	case EditorTileMap::RUZZI_OBJECT_06:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ruzzi_object_06", L"ruzzi_object_06.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ruzzi_object_06");
		pRender->Size({ 114, 75 });
		pRender->Pivot({ 26, -10.0f });
		break;

	}
	case EditorTileMap::RUZZI_OBJECT_09:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ruzzi_object_09", L"ruzzi_object_09.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"ruzzi_object_09");
		pRender->Size({ 54, 65 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::RUZZI_OBJECT_10:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ruzzi_object_10", L"ruzzi_object_10.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"ruzzi_object_10");
		pRender->Size({ 54, 65 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::RUZZI_OBJECT_11:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ruzzi_object_11", L"ruzzi_object_11.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"ruzzi_object_11");
		pRender->Size({ 54, 65 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_00:								// banifarm
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_00", L"banifarm_block_00.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_block_00");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_01", L"banifarm_block_01.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_block_01");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_02", L"banifarm_block_02.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_block_02");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_03", L"banifarm_block_03.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_block_03");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_04", L"banifarm_block_04.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_block_04");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_05", L"banifarm_block_05.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_block_05");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_06:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_06", L"banifarm_block_06.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_block_06");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_07:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_07", L"banifarm_block_07.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_block_07");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_08:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_08", L"banifarm_block_08.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_block_08");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_09:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_09", L"banifarm_block_09.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_block_09");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_10:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_10", L"banifarm_block_10.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_block_10");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_OBJECT_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_object_00", L"banifarm_object_00.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"banifarm_object_00");
		pRender->Size({ 110, 70 });
		pRender->Pivot({ 28, -6.0f });
		break;

	}
	case EditorTileMap::BANIFARM_OBJECT_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_object_02", L"banifarm_object_02.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_object_02");
		pRender->Size({ 219, 224 });
		pRender->Pivot({ 81.5f, -82.0f });
		break;

	}
	case EditorTileMap::BANIFARM_OBJECT_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_object_03", L"banifarm_object_03.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_object_03");
		pRender->Size({ 56, 67 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::BANIFARM_OBJECT_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_object_04", L"banifarm_object_04.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"banifarm_object_04");
		pRender->Size({ 56, 67 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::BANIFARM_TILE_15:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_tile_15", L"banifarm_tile_15.bmp", 0, 4, true, 0.1f);
		pRender->Animation_Change(L"banifarm_tile_15");
		pRender->Size({ 57, 60 });
		pRender->Pivot({ 1.0f, 0.0f });
		break;

	}
	case EditorTileMap::BANIFARM_TILE_16:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_tile_16", L"banifarm_tile_16.bmp", 0, 4, true, 0.1f);
		pRender->Animation_Change(L"banifarm_tile_16");
		pRender->Size({ 57, 60 });
		pRender->Pivot({ 1.0f, 0.0f });
		break;

	}
	case EditorTileMap::BANIFARM_TILE_17:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_tile_17", L"banifarm_tile_17.bmp", 0, 4, true, 0.1f);
		pRender->Animation_Change(L"banifarm_tile_17");
		pRender->Size({ 57, 60 });
		pRender->Pivot({ 1.0f, 0.0f });
		break;

	}
	case EditorTileMap::BANIFARM_TILE_18:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_tile_18", L"banifarm_tile_18.bmp", 0, 4, true, 0.1f);
		pRender->Animation_Change(L"banifarm_tile_18");
		pRender->Size({ 57, 60 });
		pRender->Pivot({ 1.0f, 0.0f });
		break;

	}
	case EditorTileMap::BANIFARM_TILE_19:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_tile_19", L"banifarm_tile_19.bmp", 0, 4, true, 0.1f);
		pRender->Animation_Change(L"banifarm_tile_19");
		pRender->Size({ 57, 60 });
		pRender->Pivot({ 1.0f, 0.0f });
		break;

	}
	case EditorTileMap::BANIFARM_TILE_20:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_tile_20", L"banifarm_tile_20.bmp", 0, 4, true, 0.1f);
		pRender->Animation_Change(L"banifarm_tile_20");
		pRender->Size({ 57, 60 });
		pRender->Pivot({ 1.0f, 0.0f });
		break;

	}
	case EditorTileMap::BANIFARM_TILE_21:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_tile_21", L"banifarm_tile_21.bmp", 0, 4, true, 0.1f);
		pRender->Animation_Change(L"banifarm_tile_21");
		pRender->Size({ 57, 60 });
		pRender->Pivot({ 1.0f, 0.0f });
		break;

	}
	case EditorTileMap::BANIFARM_TILE_22:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_tile_22", L"banifarm_tile_22.bmp", 0, 4, true, 0.1f);
		pRender->Animation_Change(L"banifarm_tile_22");
		pRender->Size({ 57, 60 });
		pRender->Pivot({ 1.0f, 0.0f });
		break;

	}
	case EditorTileMap::BANIFARM_TILE_23:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_tile_23", L"banifarm_tile_23.bmp", 0, 4, true, 0.1f);
		pRender->Animation_Change(L"banifarm_tile_23");
		pRender->Size({ 57, 60 });
		pRender->Pivot({ 1.0f, 0.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_00", L"camp_block_00.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_block_00");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_01", L"camp_block_01.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_block_01");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_02", L"camp_block_02.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_block_02");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_03", L"camp_block_03.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_block_03");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_04", L"camp_block_04.bmp", 0, 1, true, 0.05f);
		pRender->Animation_Change(L"camp_block_04");
		pRender->Size({ 65, 75 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_05", L"camp_block_05.bmp", 0, 1, true, 0.05f);
		pRender->Animation_Change(L"camp_block_05");
		pRender->Size({ 65, 75 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_06:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_06", L"camp_block_06.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_block_06");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_07:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_07", L"camp_block_07.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_block_07");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_08:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_08", L"camp_block_07.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_block_08");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_09:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_09", L"camp_block_09.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_block_09");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_10:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_10", L"camp_block_10.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_block_10");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_11:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_11", L"camp_block_11.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_block_11");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_object_00", L"camp_object_00.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_00");
		pRender->Size({ 56, 70 });
		pRender->Pivot({ 0, -6.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_object_01", L"camp_object_01.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_01");
		pRender->Size({ 56, 70 });
		pRender->Pivot({ 0, -6.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_object_02", L"camp_object_02.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_02");
		pRender->Size({ 63, 94 });
		pRender->Pivot({ 0, -13.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_object_03", L"camp_object_03.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_03");
		pRender->Size({ 63, 94 });
		pRender->Pivot({ 0, -13.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_object_04", L"camp_object_04.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_04");
		pRender->Size({ 54, 77 });
		pRender->Pivot({ 0, -10.0f });
		break;;

	}
	case EditorTileMap::CAMP_OBJECT_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_object_05", L"camp_object_05.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_05");
		pRender->Size({ 52, 87 });
		pRender->Pivot({ 0, -15.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_06:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_object_06", L"camp_object_06.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_06");
		pRender->Size({ 52, 87 });
		pRender->Pivot({ 0, -15.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_07:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_object_07", L"camp_object_07.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_07");
		pRender->Size({ 52, 87 });
		pRender->Pivot({ 0, -15.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_08:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_object_08", L"camp_object_08.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_08");
		pRender->Size({ 52, 87 });
		pRender->Pivot({ 0, -15.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_09:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_09", L"camp_object_09.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_09");
		pRender->Size({ 108, 80 });
		pRender->Pivot({ 27.0f, -13.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_10:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_10", L"camp_object_10.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_10");
		pRender->Size({ 108, 80 });
		pRender->Pivot({ -27.0f, -13.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_11:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_11", L"camp_object_11.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_11");
		pRender->Size({ 64, 84 });
		pRender->Pivot({ 0, -15.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_12:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_12", L"camp_object_12.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_12");
		pRender->Size({ 54, 70 });
		pRender->Pivot({ 0, -8.0f });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_13:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_13", L"camp_object_13.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_13");
		pRender->Size({ 60, 72 });
		pRender->Pivot({ -3.0f, -8.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_14:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_14", L"camp_object_14.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_14");
		pRender->Size({ 66, 74 });
		pRender->Pivot({ 0.0f, -10.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_15:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_15", L"camp_object_15.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_15");
		pRender->Size({ 68, 80 });
		pRender->Pivot({ 0, -13.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_16:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_16", L"camp_object_16.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_16");
		pRender->Size({ 67, 72 });
		pRender->Pivot({ -1.0f, -8.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_17:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_17", L"camp_object_17.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_17");
		pRender->Size({ 60, 82 });
		pRender->Pivot({ 0.5f, -13.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_18:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_18", L"camp_object_18.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_18");
		pRender->Size({ 60, 82 });
		pRender->Pivot({ 0.5f, -13.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_19:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_19", L"camp_object_19.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_19");
		pRender->Size({ 54, 82 });
		pRender->Pivot({ 0, -13.5f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_20:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_20", L"camp_object_20.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_20");
		pRender->Size({ 54, 82 });
		pRender->Pivot({ 0, -13.5f });
		break;
	}
	case EditorTileMap::CAMP_OBJECT_21:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_21", L"camp_object_21.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_21");
		pRender->Size({ 54, 61 });
		pRender->Pivot({ 0, -4.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_22:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"camp_object_22", L"camp_object_22.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"camp_object_22");
		pRender->Size({ 54, 61 });
		pRender->Pivot({ 0, -4.0f });
		break;

	}
	case EditorTileMap::COOKIE_BLOCK_00:					// cookie
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_00", L"cookie_block_00.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_block_00");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.5f });
		break;

	}
	case EditorTileMap::COOKIE_BLOCK_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_01", L"cookie_block_01.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_block_01");
		pRender->Size({ 59, 68 });
		pRender->Pivot({ -0.5f, -3.5f });
		break;

	}
	case EditorTileMap::COOKIE_BLOCK_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_02", L"cookie_block_02.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_block_02");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.0f });
		break;

	}
	case EditorTileMap::COOKIE_BLOCK_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_03", L"cookie_block_03.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_block_03");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.0f });
		break;

	}
	case EditorTileMap::COOKIE_BLOCK_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_04", L"cookie_block_04.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_block_04");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.0f });
		break;
	}
	case EditorTileMap::COOKIE_BLOCK_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_05", L"cookie_block_05.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_block_05");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.5f });
		break;

	}
	case EditorTileMap::COOKIE_BLOCK_06:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_06", L"cookie_block_06.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_block_06");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.5f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_00", L"cookie_object_00.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_00");
		pRender->Size({ 57, 84 });
		pRender->Pivot({ 0, -13.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_01", L"cookie_object_01.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_01");
		pRender->Size({ 57, 84 });
		pRender->Pivot({ 0, -13.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_02", L"cookie_object_02.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_02");
		pRender->Size({ 57, 88 });
		pRender->Pivot({ 0, -14.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_03", L"cookie_object_03.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_03");
		pRender->Size({ 57, 88 });
		pRender->Pivot({ 0, -14.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_04", L"cookie_object_04.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_04");
		pRender->Size({ 57, 91 });
		pRender->Pivot({ 0, -17.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_05", L"cookie_object_05.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_05");
		pRender->Size({ 57, 91 });
		pRender->Pivot({ 0, -17.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_06:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_06", L"cookie_object_06.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_06");
		pRender->Size({ 57, 91 });
		pRender->Pivot({ 0, -17.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_07:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_07", L"cookie_object_07.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_07");
		pRender->Size({ 57, 98 });
		pRender->Pivot({ 0, -19.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_08:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_08", L"cookie_object_08.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_08");
		pRender->Size({ 57, 98 });
		pRender->Pivot({ 0, -19.0f });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_09:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_09", L"cookie_object_09.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_09");
		pRender->Size({ 113, 95 });
		pRender->Pivot({ 26.0f, -18.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_10:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_10", L"cookie_object_10.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_10");
		pRender->Size({ 113, 95 });
		pRender->Pivot({ 26.0f, -18.0f });
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_11:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_11", L"cookie_object_11.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_11");
		pRender->Size({ 235, 180 });
		pRender->Pivot({ 82.0f, -61.5f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_12:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_12", L"cookie_object_12.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_12");
		pRender->Size({ 107, 148 });
		pRender->Pivot({ 27.0f, -45.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_13:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"cookie_object_13", L"cookie_object_13.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_13");
		pRender->Size({ 107, 148 });
		pRender->Pivot({ 26.0f, -40.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_14:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_14", L"cookie_object_14.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_14");
		pRender->Size({ 110, 120 });
		pRender->Pivot({ 28.0f, -33.0f });
		break;

	}
	case EditorTileMap::COOKIE_OBJECT_15:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_object_15", L"cookie_object_15.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_object_15");
		pRender->Size({ 110, 120 });
		pRender->Pivot({ 28.0f, -33.0f });
		break;
	}
	case EditorTileMap::COOKIE_TILE_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_tile_03", L"cookie_tile_03.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"cookie_tile_03");
		pRender->Size({ 55, 55 });
		pRender->Pivot({ 0.0f, 0.0f });
		break;

	}
	// desert~sea 

	case EditorTileMap::DESERT_BLOCK_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_block_00", L"desert_block_00.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_block_00");
		pRender->Size({ 60, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::DESERT_BLOCK_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_block_01", L"desert_block_01.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_block_01");
		pRender->Size({ 60, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::DESERT_BLOCK_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_block_02", L"desert_block_02.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_block_02");
		pRender->Size({ 60, 73 });
		pRender->Pivot({ 0, -4.0f });
		break;
	}
	case EditorTileMap::DESERT_BLOCK_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_block_03", L"desert_block_03.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_block_03");
		pRender->Size({ 60, 70 });
		pRender->Pivot({ 0, -4.5f });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_00", L"desert_object_00.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_00");
		pRender->Size({ 54, 90 });
		pRender->Pivot({ 0, -15.0f });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_01", L"desert_object_01.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_01");
		pRender->Size({ 54, 90 });
		pRender->Pivot({ 0, -15.0f });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_02", L"desert_object_02.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_02");
		pRender->Size({ 54, 90 });
		pRender->Pivot({ 0, -15.0f });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_03", L"desert_object_03.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_03");
		pRender->Size({ 54, 90 });
		pRender->Pivot({ 0, -15.0f });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_04", L"desert_object_04.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"desert_object_04");
		pRender->Size({ 100, 100 });
		pRender->Pivot({ 25, -20.0f });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_05", L"desert_object_05.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_05");
		pRender->Size({ 54, 69 });
		pRender->Pivot({ 0, -8.0f });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_06:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_06", L"desert_object_06.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_06");
		pRender->Size({ 54, 90 });
		pRender->Pivot({ 0, -17.0f });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_07:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_07", L"desert_object_07.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_07");
		pRender->Size({ 54, 90 });
		pRender->Pivot({ 0, -17.0f });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_08:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_08", L"desert_object_08.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_08");
		pRender->Size({ 54, 90 });
		pRender->Pivot({ 0, -17.0f });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_09:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_09", L"desert_object_09.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_09");
		pRender->Size({ 62, 97 });
		pRender->Pivot({ 2, -19 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_10:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_10", L"desert_object_10.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_10");
		pRender->Size({ 62, 97 });
		pRender->Pivot({ 2, -19 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_11:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_11", L"desert_object_11.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_11");
		pRender->Size({ 62, 97 });
		pRender->Pivot({ 2, -19 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_12:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_12", L"desert_object_12.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_12");
		pRender->Size({ 83, 116 });
		pRender->Pivot({ -5, -25 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_13:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_13", L"desert_object_13.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_13");
		pRender->Size({ 83, 116 });
		pRender->Pivot({ -5, -25 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_14:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_14", L"desert_object_14.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_14");
		pRender->Size({ 54, 90 });
		pRender->Pivot({ 0, -18 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_15:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_15", L"desert_object_15.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_15");
		pRender->Size({ 54, 90 });
		pRender->Pivot({ 0, -18 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_16:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_16", L"desert_object_16.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_16");
		pRender->Size({ 54, 90 });
		pRender->Pivot({ 0, -18 });
		break;
	}
	case EditorTileMap::DESERT_OBJECT_17_DUMMY:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_object_17_dummy", L"desert_object_17_dummy.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"desert_object_17_dummy");
		pRender->Size({ 54, 90 });
		pRender->Pivot({ 0, -18 });
		break;
	}
	case EditorTileMap::ICE_BLOCK_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_block_00", L"ice_block_00.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_block_00");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ -0.5f, -6.0f });
		break;
	}
	case EditorTileMap::ICE_BLOCK_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_block_01", L"ice_block_01.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_block_01");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ -0.5f, -6.0f });
		break;
	}
	case EditorTileMap::ICE_BLOCK_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_block_02", L"ice_block_02.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_block_02");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ -0.5f, -6.0f });
		break;
	}
	case EditorTileMap::ICE_BLOCK_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_block_03", L"ice_block_03.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_block_03");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ -0.5f, -4.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_00", L"ice_object_00.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_00");
		pRender->Size({ 55, 77 });
		pRender->Pivot({ 0, -8.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_01", L"ice_object_01.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_01");
		pRender->Size({ 55, 77 });
		pRender->Pivot({ 0, -8.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_02", L"ice_object_02.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_02");
		pRender->Size({ 55, 77 });
		pRender->Pivot({ 0, -8.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_03", L"ice_object_03.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_03");
		pRender->Size({ 55, 77 });
		pRender->Pivot({ 0, -8.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_04", L"ice_object_04.bmp", 0, 6, true, 0.1f);
		pRender->Animation_Change(L"ice_object_04");
		pRender->Size({ 108, 108 });
		pRender->Pivot({ 27.5f, -26.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_05", L"ice_object_05.bmp", 0, 3, true, 0.1f);
		pRender->Animation_Change(L"ice_object_05");
		pRender->Size({ 108, 108 });
		pRender->Pivot({ 27.5f, -23.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_06:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_06", L"ice_object_06.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_06");
		pRender->Size({ 162, 158 });
		pRender->Pivot({ 54, -50.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_07:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_07", L"ice_object_07.bmp", 0, 2, true, 0.5f);
		pRender->Animation_Change(L"ice_object_07");
		pRender->Size({ 54, 93 });
		pRender->Pivot({ 0, -17.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_08:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_08", L"ice_object_08.bmp", 0, 2, true, 0.5f);
		pRender->Animation_Change(L"ice_object_08");
		pRender->Size({ 54, 93 });
		pRender->Pivot({ 0, -17.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_09:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_09", L"ice_object_09.bmp", 0, 2, true, 0.5f);
		pRender->Animation_Change(L"ice_object_09");
		pRender->Size({ 54, 93 });
		pRender->Pivot({ 0, -17.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_10:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_10", L"ice_object_10.bmp", 0, 2, true, 0.5f);
		pRender->Animation_Change(L"ice_object_10");
		pRender->Size({ 54, 93 });
		pRender->Pivot({ 0, -17.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_11:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_11", L"ice_object_11.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_11");
		pRender->Size({ 54, 95 });
		pRender->Pivot({ 0, -17.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_12:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_12", L"ice_object_12.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_12");
		pRender->Size({ 56, 86 });
		pRender->Pivot({ 0, -15.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_13:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_13", L"ice_object_13.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_13");
		pRender->Size({ 56, 78 });
		pRender->Pivot({ 0, -13.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_14:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"ice_object_14", L"ice_object_14.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_14");
		pRender->Size({ 56, 78 });
		pRender->Pivot({ 0, -13.0f });
		break;
	}
	case EditorTileMap::ICE_OBJECT_15:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_15", L"ice_object_15.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_15");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_16:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_16", L"ice_object_16.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_16");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_17:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_17", L"ice_object_17.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_17");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_18:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_18", L"ice_object_18.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_18");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_19:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_19", L"ice_object_19.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_19");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_20:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_20", L"ice_object_20.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_20");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_21:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_21", L"ice_object_21.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_21");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_22:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_22", L"ice_object_22.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_22");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_OBJECT_23:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_object_23", L"ice_object_23.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"ice_object_23");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_TILE_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(8);
		pRender->Animation_Create(L"ice_tile_02", L"ice_tile_02.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ice_tile_02");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_TILE_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(8);
		pRender->Animation_Create(L"ice_tile_03", L"ice_tile_03.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ice_tile_03");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_TILE_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(8);
		pRender->Animation_Create(L"ice_tile_04", L"ice_tile_04.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ice_tile_04");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_TILE_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(8);
		pRender->Animation_Create(L"ice_tile_05", L"ice_tile_05.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ice_tile_05");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_TILE_06:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(8);
		pRender->Animation_Create(L"ice_tile_06", L"ice_tile_06.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ice_tile_06");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_TILE_07:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(8);
		pRender->Animation_Create(L"ice_tile_07", L"ice_tile_07.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ice_tile_07");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_TILE_08:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(8);
		pRender->Animation_Create(L"ice_tile_08", L"ice_tile_08.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ice_tile_08");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_TILE_09:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(8);
		pRender->Animation_Create(L"ice_tile_09", L"ice_tile_09.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ice_tile_09");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_TILE_10:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(8);
		pRender->Animation_Create(L"ice_tile_10", L"ice_tile_10.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ice_tile_10");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_TILE_11:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(8);
		pRender->Animation_Create(L"ice_tile_11", L"ice_tile_11.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ice_tile_11");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::ICE_TILE_12:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(8);
		pRender->Animation_Create(L"ice_tile_12", L"ice_tile_12.bmp", 0, 2, true, 0.1f);
		pRender->Animation_Change(L"ice_tile_12");
		pRender->Size({ 54, 55 });
		pRender->Pivot({ 0, 0 });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_00:									// Pirate
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_block_00", L"pirate_block_00.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_block_00");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_block_01", L"pirate_block_01.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_block_01");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_block_02", L"pirate_block_02.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_block_02");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_block_03", L"pirate_block_03.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_block_03");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(10);
		pRender->Animation_Create(L"pirate_block_04", L"pirate_block_04.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_block_04");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_00", L"pirate_object_00.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_00");
		pRender->Size({ 54, 81 });
		pRender->Pivot({ 0, -13.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_01", L"pirate_object_01.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_01");
		pRender->Size({ 54, 81 });
		pRender->Pivot({ 0, -13.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_02", L"pirate_object_02.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_02");
		pRender->Size({ 54, 81 });
		pRender->Pivot({ 0, -13.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_03", L"pirate_object_03.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_03");
		pRender->Size({ 54, 119 });
		pRender->Pivot({ 0, -30 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_04", L"pirate_object_04.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_04");
		pRender->Size({ 54, 119 });
		pRender->Pivot({ 0, -30 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_05", L"pirate_object_05.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_05");
		pRender->Size({ 190, 200 });
		pRender->Pivot({ 60, -72 });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_06:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_06", L"pirate_object_06.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_06");
		pRender->Size({ 54, 64 });
		pRender->Pivot({ 0, -4.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_07:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_07", L"pirate_object_07.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_07");
		pRender->Size({ 54, 86 });
		pRender->Pivot({ 0, -15.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_08:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_08", L"pirate_object_08.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_08");
		pRender->Size({ 54, 86 });
		pRender->Pivot({ 0, -15.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_09:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_09", L"pirate_object_09.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_09");
		pRender->Size({ 54, 78 });
		pRender->Pivot({ 0, -12.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_10:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_10", L"pirate_object_10.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_10");
		pRender->Size({ 54, 104 });
		pRender->Pivot({ 0, -24.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_11:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_11", L"pirate_object_11.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_11");
		pRender->Size({ 78, 169 });
		pRender->Pivot({ 0, -57.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_12:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_12", L"pirate_object_12.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_12");
		pRender->Size({ 54, 78 });
		pRender->Pivot({ 0, -11.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_13:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_13", L"pirate_object_13.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_13");
		pRender->Size({ 54, 100 });
		pRender->Pivot({ 0, -22.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_14:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_14", L"pirate_object_14.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_14");
		pRender->Size({ 54, 106 });
		pRender->Pivot({ 0, -25.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_15:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_15", L"pirate_object_15.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_15");
		pRender->Size({ 54, 92 });
		pRender->Pivot({ 0, -18.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_16:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_16", L"pirate_object_16.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_16");
		pRender->Size({ 59, 82 });
		pRender->Pivot({ 0, -15.0f });
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_17:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_object_17", L"pirate_object_17.bmp", 0, 0, true, 0.1f);
		pRender->Animation_Change(L"pirate_object_17");
		pRender->Size({ 54, 92 });
		pRender->Pivot({ 0, -18.0f });
		break;
	}
	case EditorTileMap::VILAGE_BLOCK_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_block_00", L"vilage_block_00.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"vilage_block_00");
		pRender->Size({ 60, 70 });
		pRender->Pivot({ 0.5f, -5.5f });
		break;
	}
	case EditorTileMap::VILAGE_BLOCK_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_block_01", L"vilage_block_01.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"vilage_block_01");
		pRender->Size({ 60, 75 });
		pRender->Pivot({ 0.5f, -5.0f });
		break;
	}
	case EditorTileMap::VILAGE_BLOCK_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_block_02", L"vilage_block_02.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"vilage_block_02");
		pRender->Size({ 60, 75 });
		pRender->Pivot({ 0.5f, -5.0f });
		break;
	}
	case EditorTileMap::VILAGE_BLOCK_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_block_03", L"vilage_block_03.bmp", 0, 1, true, 0.08f);
		pRender->Animation_Change(L"vilage_block_03");
		pRender->Size({ 68, 110 });
		pRender->Pivot({ 0, -12.0f });
		break;
	}
	case EditorTileMap::VILAGE_OBJECT_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_object_00", L"vilage_object_00.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"vilage_object_00");
		pRender->Size({ 57, 86 });
		pRender->Pivot({ 0, -14.0f });
		break;

	}
	case EditorTileMap::VILAGE_OBJECT_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_object_01", L"vilage_object_01.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"vilage_object_01");
		pRender->Size({ 57, 81 });
		pRender->Pivot({ 0, -12.0f });
		break;

	}
	case EditorTileMap::VILAGE_OBJECT_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_object_02", L"vilage_object_02.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"vilage_object_02");
		pRender->Size({ 57, 81 });
		pRender->Pivot({ 0, -12.0f });
		break;

	}
	case EditorTileMap::VILAGE_OBJECT_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_object_03", L"vilage_object_03.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"vilage_object_03");
		pRender->Size({ 54, 94 });
		pRender->Pivot({ 1.0f, -15.0f });
		break;

	}
	case EditorTileMap::VILAGE_OBJECT_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_object_04", L"vilage_object_04.bmp", 0, 2, true, 0.3f);
		pRender->Animation_Change(L"vilage_object_04");
		pRender->Size({ 159, 238 });
		pRender->Pivot({ 56.0f, -90.0f });
		break;

	}
	case EditorTileMap::VILAGE_OBJECT_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_object_05", L"vilage_object_05.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"vilage_object_05");
		pRender->Size({ 150, 115 });
		pRender->Pivot({ 55.0f, -29.0f });
		break;

	}
	case EditorTileMap::VILAGE_OBJECT_12:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_object_12", L"vilage_object_12.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"vilage_object_12");
		pRender->Size({ 233, 108 });
		pRender->Pivot({ 50.0f, -5.0f });
		break;

	}
	case EditorTileMap::OBJTYPE_MAX:
		break;
	default:
		break;
	}




	TileMapRenderer::Tile* pTile = m_pTileRenderer->Find_ScreenPosTile(_Pos);

	if (pTile == nullptr)
	{
		return nullptr;
	}

	pTile->ObjIndex = _Index;			// 타일 인덱스


	// 6월30일 추가 - 여러 타일을 침범하는 블럭들 타일 인덱스 추가해주기
	VECTOR2_INT AddTileIndex = VECTOR2_INT{ 0, 0 };
	F_Position AddTilePos = F_Position{ 0,0 };
	TileMapRenderer::Tile* pAddTile = nullptr;

	switch (_Index)
	{
	case EditorTileMap::BANIFARM_OBJECT_00:			// 물웅덩이
	{
		AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
		AddTileIndex = AddTileIndex + VECTOR2_INT{ 1,0 };
		AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

		pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

		if (pAddTile == nullptr)
		{
			break;
		}
		pAddTile->ObjIndex = OBJTYPE_MAX;			// 타일 인덱스


		break;
	}
	case EditorTileMap::BANIFARM_OBJECT_02:			// 집
	{

		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 4; x++)
			{
				int a = 0;
				if (0 >= x && y >= 0)
					continue;
		
				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = (VECTOR2_INT)AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_09:			// 딸기 케이크
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_10:			// 블루베리 케이크
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;

			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_11:			// 달콤한 왕배찌
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 4; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_12:			// 너구리 케이크
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_13:			// 커피
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_14:			// 왕도넛
	{
		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_15:			// 왕도넛 2층
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::DESERT_OBJECT_04:			// 야자수 + 물
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::ICE_OBJECT_04:				// 빨간 지붕 집
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::ICE_OBJECT_05:				// 나무집
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::ICE_OBJECT_06:				// 이글루
	{
		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 3; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_05:			// 깃발
	{
		int a = 0;
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 3; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}

		break;
	}
	case EditorTileMap::VILAGE_OBJECT_04:			// 풍차
	{
		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 3; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::VILAGE_OBJECT_12:			// 비행기
	{	
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::NONE:
		break;
	case EditorTileMap::OBJTYPE_MAX:
		break;
	default:
		break;
	}


	m_ObjTile.insert(std::map<__int64, ActorObjBase*>::value_type(Index, Obj));		// 오브젝트인덱스, 오브젝트 넣기
	
	if (Obj == nullptr)
	{
		return nullptr;			// 2개 이상 차지하는 블럭 때문에 /..
	}
	
	Obj->Pos(_Pos);

	if (true == m_bEditorMode)
	{
		pTile->ItemType = Create_ItemType(_Index);
	}

	return Obj;
}

// 나무 상자 같은 움직일 수 있는 블럭들 생성 ( 타입, 바뀐후의 위치, 키보드 방향키 )
ActorObjBase* EditorTileMap::CreateMoveObjIndex(OBJTYPE _Index, F_Position _Pos, std::wstring _Dir)
{
	VECTOR2_INT ChangeIndexAfter = m_pTileRenderer->OriginTileIndex(_Pos);
	VECTOR2_INT ChangeIndexBefore = ChangeIndexAfter;

	F_Position ChangeBeforePos = { -1, -1 };

	if (ChangeIndexAfter.X < 0 || ChangeIndexAfter.Y < 0)
	{
		return nullptr;
	}


	if (L"UP" == _Dir)
	{
		int v = 3;
		ChangeIndexBefore = (VECTOR2_INT)ChangeIndexAfter + VECTOR2_INT{ 0, 1 };		// 블록의 원래 위치(바뀌기전의 위치)
		ChangeBeforePos = m_pTileRenderer->OriginTilePos(ChangeIndexBefore);
	}
	else if (L"DOWN" == _Dir)
	{
		ChangeIndexBefore = (VECTOR2_INT)ChangeIndexAfter + VECTOR2_INT{ 0, -1 };		// 블록의 원래 위치(바뀌기전의 위치)
		ChangeBeforePos = m_pTileRenderer->OriginTilePos(ChangeIndexBefore);
	}
	else if (L"LEFT" == _Dir)
	{
		ChangeIndexBefore = (VECTOR2_INT)ChangeIndexAfter + VECTOR2_INT{ 1, 0 };		// 블록의 원래 위치(바뀌기전의 위치)
		ChangeBeforePos = m_pTileRenderer->OriginTilePos(ChangeIndexBefore);
	}
	else if (L"RIGHT" == _Dir)
	{
		ChangeIndexBefore = (VECTOR2_INT)ChangeIndexAfter + VECTOR2_INT{ -1,0  };		// 블록의 원래 위치(바뀌기전의 위치)
		ChangeBeforePos = m_pTileRenderer->OriginTilePos(ChangeIndexBefore);
	}
	else
	{
		return nullptr;
	}

	ActorObjBase* Obj = nullptr;
	AnimationRenderer* pRender = nullptr;

	std::map<__int64, ActorObjBase*>::iterator BeforeFind_Iter = m_ObjTile.find(ChangeIndexBefore);


	switch (_Index)
	{
	case EditorTileMap::VILAGE_BLOCK_00:
	{
		OriginBlock_Delete(ChangeIndexBefore);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_block_00", L"vilage_block_00.bmp", 0, 1, true, 0.1f);
		pRender->Animation_Change(L"vilage_block_00");
		pRender->Size({ 60, 70 });
		pRender->Pivot({ 0.5f, -5.5f });
		break;
	}
	default:
		break;
	}




	TileMapRenderer::Tile* pTile = m_pTileRenderer->Find_ScreenPosTile(_Pos);
	TileMapRenderer::Tile* pTileBefore = m_pTileRenderer->Find_ScreenPosTile(ChangeBeforePos);

	if (pTile == nullptr)
	{
		return nullptr;
	}

	pTile->ObjIndex = _Index;			// 타일 인덱스

	std::map<__int64, ActorObjBase*>::iterator BeforeIter = m_ObjTile.find(ChangeIndexAfter);

	if (BeforeIter != m_ObjTile.end())
	{
		int a = 0;
		m_ObjTile.erase(BeforeIter);
	}

	m_ObjTile.insert(std::map<__int64, ActorObjBase*>::value_type(ChangeIndexAfter, Obj));		// 오브젝트인덱스, 오브젝트 넣기
	Obj->Pos(_Pos);			// 바뀐 위치

	if (true == m_bEditorMode)
	{
		pTile->ItemType = Create_ItemType(_Index);
	}

	return Obj;
}

// 삭제할수 있는 블럭 애니메이션 실행하기 + 아이템 생성
ActorObjBase* EditorTileMap::Block_Animation(EditorTileMap::OBJTYPE _Type, F_Position _Pos)
{
	VECTOR2_INT Index = m_pTileRenderer->OriginTileIndex(_Pos);

	ActorObjBase* Obj = nullptr;


	switch (_Type)
	{
	case EditorTileMap::BANIFARM_BLOCK_00:								// banifarm
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_00", L"banifarm_block_00.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"banifarm_block_00");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_01:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_01", L"banifarm_block_01.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"banifarm_block_01");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_02:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_02", L"banifarm_block_02.bmp", 0, 8, false, 0.1f);
		pRender->Animation_Change(L"banifarm_block_02");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_03:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_03", L"banifarm_block_03.bmp", 0, 8, false, 0.1f);
		pRender->Animation_Change(L"banifarm_block_03");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_04:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_04", L"banifarm_block_04.bmp", 0, 8, false, 0.1f);
		pRender->Animation_Change(L"banifarm_block_04");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_05:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_05", L"banifarm_block_05.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"banifarm_block_05");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_06:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_06", L"banifarm_block_06.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"banifarm_block_06");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_07:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_07", L"banifarm_block_07.bmp", 0, 8, false, 0.1f);
		pRender->Animation_Change(L"banifarm_block_07");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_08:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_08", L"banifarm_block_08.bmp", 0, 8, false, 0.1f);
		pRender->Animation_Change(L"banifarm_block_08");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_09:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_09", L"banifarm_block_09.bmp", 0, 8, false, 0.1f);
		pRender->Animation_Change(L"banifarm_block_09");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}
	case EditorTileMap::BANIFARM_BLOCK_10:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"banifarm_block_10", L"banifarm_block_10.bmp", 0, 8, false, 0.1f);
		pRender->Animation_Change(L"banifarm_block_10");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ 0, -7.0f });
		break;

	}

	case EditorTileMap::CAMP_BLOCK_00:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_00", L"camp_block_00.bmp", 0, 6, false, 0.1f);
		pRender->Animation_Change(L"camp_block_00");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_01:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_01", L"camp_block_01.bmp", 0, 6, false, 0.1f);
		pRender->Animation_Change(L"camp_block_01");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_02", L"camp_block_02.bmp", 0, 6, false, 0.1f);
		pRender->Animation_Change(L"camp_block_02");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_03", L"camp_block_03.bmp", 0, 6, false, 0.1f);
		pRender->Animation_Change(L"camp_block_03");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::CAMP_BLOCK_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_04", L"camp_block_04.bmp", 0, 5, false, 0.05f);
		pRender->Animation_Change(L"camp_block_04");
		pRender->Size({ 65, 75 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_05", L"camp_block_05.bmp", 0, 5, false, 0.05f);
		pRender->Animation_Change(L"camp_block_05");
		pRender->Size({ 65, 75 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_06:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_06", L"camp_block_06.bmp", 0, 9, false, 0.1f);
		pRender->Animation_Change(L"camp_block_06");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_07:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_07", L"camp_block_07.bmp", 0, 9, false, 0.1f);
		pRender->Animation_Change(L"camp_block_07");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_08:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_08", L"camp_block_07.bmp", 0, 9, false, 0.1f);
		pRender->Animation_Change(L"camp_block_08");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_09:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_09", L"camp_block_09.bmp", 0, 9, false, 0.1f);
		pRender->Animation_Change(L"camp_block_09");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_10:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_10", L"camp_block_10.bmp", 0, 6, false, 0.1f);
		pRender->Animation_Change(L"camp_block_10");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}

	case EditorTileMap::COOKIE_BLOCK_00:					// cookie
	{

		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_00", L"cookie_block_00.bmp", 0, 8, false, 0.1f);
		pRender->Animation_Change(L"cookie_block_00");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.5f });
		break;

	}
	case EditorTileMap::COOKIE_BLOCK_01:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_01", L"cookie_block_01.bmp", 0, 8, false, 0.1f);
		pRender->Animation_Change(L"cookie_block_01");
		pRender->Size({ 59, 68 });
		pRender->Pivot({ -0.5f, -3.5f });
		break;

	}
	case EditorTileMap::COOKIE_BLOCK_02:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_02", L"cookie_block_02.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"cookie_block_02");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.0f });
		break;

	}
	case EditorTileMap::COOKIE_BLOCK_03:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_03", L"cookie_block_03.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"cookie_block_03");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.0f });
		break;

	}
	case EditorTileMap::COOKIE_BLOCK_04:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_04", L"cookie_block_04.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"cookie_block_04");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.0f });
		break;
	}
	case EditorTileMap::COOKIE_BLOCK_05:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_05", L"cookie_block_05.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"cookie_block_05");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.5f });
		break;

	}
	case EditorTileMap::COOKIE_BLOCK_06:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"cookie_block_06", L"cookie_block_06.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"cookie_block_06");
		pRender->Size({ 60, 68 });
		pRender->Pivot({ 0, -3.5f });
		break;

	}

	case EditorTileMap::DESERT_BLOCK_00:				// desert
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_block_00", L"desert_block_00.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"desert_block_00");
		pRender->Size({ 60, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::DESERT_BLOCK_01:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_block_01", L"desert_block_01.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"desert_block_01");
		pRender->Size({ 60, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::DESERT_BLOCK_02:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_block_02", L"desert_block_02.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"desert_block_02");
		pRender->Size({ 60, 73 });
		pRender->Pivot({ 0, -4.0f });
		break;
	}
	case EditorTileMap::DESERT_BLOCK_03:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"desert_block_03", L"desert_block_03.bmp", 0, 8, false, 0.1f);
		pRender->Animation_Change(L"desert_block_03");
		pRender->Size({ 60, 70 });
		pRender->Pivot({ 0, -4.5f });
		break;
	}

	case EditorTileMap::ICE_BLOCK_00:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_block_00", L"ice_block_00.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"ice_block_00");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ -0.5f, -6.0f });
		break;
	}
	case EditorTileMap::ICE_BLOCK_01:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_block_01", L"ice_block_01.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"ice_block_01");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ -0.5f, -6.0f });
		break;
	}
	case EditorTileMap::ICE_BLOCK_02:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_block_02", L"ice_block_02.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"ice_block_02");
		pRender->Size({ 59, 75 });
		pRender->Pivot({ -0.5f, -6.0f });
		break;
	}
	case EditorTileMap::ICE_BLOCK_03:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"ice_block_03", L"ice_block_03.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"ice_block_03");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ -0.5f, -4.0f });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_00:									// Pirate
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_block_00", L"pirate_block_00.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"pirate_block_00");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_01:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_block_01", L"pirate_block_01.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"pirate_block_01");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_02:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_block_02", L"pirate_block_02.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"pirate_block_02");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_03:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_block_03", L"pirate_block_03.bmp", 0, 8, false, 0.1f);
		pRender->Animation_Change(L"pirate_block_03");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}
	case EditorTileMap::PIRATE_BLOCK_04:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"pirate_block_04", L"pirate_block_04.bmp", 0, 5, false, 0.1f);
		pRender->Animation_Change(L"pirate_block_04");
		pRender->Size({ 59, 70 });
		pRender->Pivot({ 0, -5.0f });
		break;
	}

	case EditorTileMap::VILAGE_BLOCK_00:					// vilage
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_block_00", L"vilage_block_00.bmp", 0, 6, false, 0.1f);
		pRender->Animation_Change(L"vilage_block_00");
		pRender->Size({ 60, 70 });
		pRender->Pivot({ 0.5f, -5.5f });
		break;
	}
	case EditorTileMap::VILAGE_BLOCK_01:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_block_01", L"vilage_block_01.bmp", 0, 6, false, 0.1f);
		pRender->Animation_Change(L"vilage_block_01");
		pRender->Size({ 60, 75 });
		pRender->Pivot({ 0.5f, -5.0f });
		break;
	}
	case EditorTileMap::VILAGE_BLOCK_02:
	{
		OriginBlock_Delete(Index);
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_block_02", L"vilage_block_02.bmp", 0, 6, false, 0.1f);
		pRender->Animation_Change(L"vilage_block_02");
		pRender->Size({ 60, 75 });
		pRender->Pivot({ 0.5f, -5.0f });
		break;
	}
	case EditorTileMap::VILAGE_BLOCK_03:
	{
		OriginBlockMove_Delete(Index);
		OriginBlock_Delete(Index);


		std::map<__int64, ActorObjBase*>::iterator Start_Iter = m_BlockjAni.begin();
		std::map<__int64, ActorObjBase*>::iterator End_Iter = m_BlockjAni.end();

		for (; Start_Iter != End_Iter;++Start_Iter)
		{
			Start_Iter->second->Obj_Death();
		}
		m_BlockjAni.clear();

		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_block_03", L"vilage_block_03.bmp", 0, 5, false, 0.05f);
		pRender->Animation_Change(L"vilage_block_03");
		pRender->Size({ 68, 110 });
		pRender->Pivot({ 0, -12.0f });
		break;
	}
	default:
		break;
	}

	if (Obj == nullptr)
	{
		return nullptr;
	}


	TileMapRenderer::Tile* pTile = m_pTileRenderer->Find_ScreenPosTile(_Pos);

	if (pTile == nullptr)
	{
		return nullptr;
	}


	Create_Item(Index, pTile);		// 아이템 생성

	pTile->ObjIndex = -1;			// 타일 인덱스 ( 캐릭터가 이동할 수 있게 바꿈)
										//VECTOR2_INT Index = m_pTileRenderer->OriginTileIndex(_Pos);

	m_BlockjAni.insert(std::map<__int64, ActorObjBase*>::value_type(Index, Obj));		// 오브젝트인덱스, 오브젝트 넣기
	Obj->Pos(_Pos);

	return Obj;
}

ActorObjBase* EditorTileMap::Block_AnimationNoneItem(EditorTileMap::OBJTYPE _Type, F_Position _Pos)
{
	VECTOR2_INT Index = m_pTileRenderer->OriginTileIndex(_Pos);

	ActorObjBase* Obj = nullptr;

	switch (_Type)
	{
	case EditorTileMap::CAMP_BLOCK_04:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_04", L"camp_block_04.bmp", 0, 5, false, 0.05f);
		pRender->Animation_Change(L"camp_block_04");
		pRender->Size({ 65, 75 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_BLOCK_05:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_block_05", L"camp_block_05.bmp", 0, 5, false, 0.05f);
		pRender->Animation_Change(L"camp_block_05");
		pRender->Size({ 65, 75 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_02:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_object_02", L"camp_object_02.bmp", 0, 3, false, 0.1f);
		pRender->Animation_Change(L"camp_object_02");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::CAMP_OBJECT_03:
	{
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"camp_object_03", L"camp_object_03.bmp", 0, 3, false, 0.1f);
		pRender->Animation_Change(L"camp_block_07");
		pRender->Size({ 58, 66 });
		pRender->Pivot({ 0, -5.0f });
		break;

	}
	case EditorTileMap::VILAGE_BLOCK_03:
	{
		OriginBlockMove_Delete(Index);
		//OriginBlock_Delete(Index);
		int a = 0;
		std::map<__int64, ActorObjBase*>::iterator Start_Iter = m_BlockjAni.begin();
		std::map<__int64, ActorObjBase*>::iterator End_Iter = m_BlockjAni.end();

		for (; Start_Iter != End_Iter; ++Start_Iter)
		{
			Start_Iter->second->Obj_Death();
		}
		m_BlockjAni.clear();


		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		pRender->Animation_Create(L"vilage_block_Move_03", L"vilage_block_Move_03.bmp", 0, 5, false, 0.05f);
		pRender->Animation_Change(L"vilage_block_Move_03");
		pRender->Size({ 68, 110 });
		pRender->Pivot({ 0, -12.0f });
		break;
	}
	default:
		break;
	}

	if (Obj == nullptr)
	{
		return nullptr;
	}

	TileMapRenderer::Tile* pTile = m_pTileRenderer->Find_ScreenPosTile(_Pos);

	if (pTile == nullptr)
	{
		return nullptr;
	}


	m_BlockjAni.insert(std::map<__int64, ActorObjBase*>::value_type(Index, Obj));		// 오브젝트인덱스, 오브젝트 넣기
	m_ObjTile.insert(std::map<__int64, ActorObjBase*>::value_type(Index, Obj));
	Obj->Pos(_Pos);

	return Obj;
}

// 아이템
int EditorTileMap::Create_ItemType(OBJTYPE _Type)
{
	int ItemRand = 0;
	srand(GetTickCount());			// 컴퓨터 부팅 이후 시간으로 값이 실시간으로 변함 ( 변하는 속도 : 1/1000초 )

	switch (_Type)
	{
	case EditorTileMap::BANIFARM_BLOCK_00:								// banifarm
	case EditorTileMap::BANIFARM_BLOCK_01:
	case EditorTileMap::BANIFARM_BLOCK_02:
	case EditorTileMap::BANIFARM_BLOCK_03:
	case EditorTileMap::BANIFARM_BLOCK_04:
	case EditorTileMap::BANIFARM_BLOCK_05:
	case EditorTileMap::BANIFARM_BLOCK_06:
	case EditorTileMap::BANIFARM_BLOCK_07:
	case EditorTileMap::BANIFARM_BLOCK_08:
	case EditorTileMap::BANIFARM_BLOCK_09:
	case EditorTileMap::BANIFARM_BLOCK_10:

	case EditorTileMap::CAMP_BLOCK_00:
	case EditorTileMap::CAMP_BLOCK_01:
	case EditorTileMap::CAMP_BLOCK_02:
	case EditorTileMap::CAMP_BLOCK_03:
	case EditorTileMap::CAMP_BLOCK_04:
	case EditorTileMap::CAMP_BLOCK_05:
	case EditorTileMap::CAMP_BLOCK_06:
	case EditorTileMap::CAMP_BLOCK_07:

	case EditorTileMap::DESERT_BLOCK_00:						// Desert
	case EditorTileMap::DESERT_BLOCK_01:
	case EditorTileMap::DESERT_BLOCK_02:
	case EditorTileMap::DESERT_BLOCK_03:

	case EditorTileMap::ICE_BLOCK_00:						// Ice
	case EditorTileMap::ICE_BLOCK_01:
	case EditorTileMap::ICE_BLOCK_02:
	case EditorTileMap::ICE_BLOCK_03:

	case EditorTileMap::PIRATE_BLOCK_00:						// pirate
	case EditorTileMap::PIRATE_BLOCK_01:
	case EditorTileMap::PIRATE_BLOCK_02:
	case EditorTileMap::PIRATE_BLOCK_03:
	case EditorTileMap::PIRATE_BLOCK_04:

	case EditorTileMap::CAMP_BLOCK_08:
	case EditorTileMap::CAMP_BLOCK_09:
	case EditorTileMap::CAMP_BLOCK_10:
	case EditorTileMap::COOKIE_BLOCK_00:					// cookie
	case EditorTileMap::COOKIE_BLOCK_01:
	case EditorTileMap::COOKIE_BLOCK_02:
	case EditorTileMap::COOKIE_BLOCK_03:
	case EditorTileMap::COOKIE_BLOCK_04:
	case EditorTileMap::COOKIE_BLOCK_05:
	case EditorTileMap::COOKIE_BLOCK_06:

	case EditorTileMap::VILAGE_BLOCK_00:					// vilage
	case EditorTileMap::VILAGE_BLOCK_01:
	case EditorTileMap::VILAGE_BLOCK_02:
	case EditorTileMap::VILAGE_BLOCK_03:
		// 아이템 종류 결정

		ItemRand = rand() % 14;			// 0 ~ 15까지의 값
		break;
	default:
		break;
	}

	return ItemRand;
}

void EditorTileMap::Delete_ItemType(TileMapRenderer::Tile* _Tile)
{
	_Tile->ItemType = 0;
}

void EditorTileMap::Create_Item(VECTOR2_INT _Index, TileMapRenderer::Tile* _Tile)
{
	Item::ITEM_TYPE ItemType = (Item::ITEM_TYPE)(_Tile->ItemType);

	F_Position ItemPos = m_pTileRenderer->OriginTilePos(_Index);

	int randCoinItem = rand() % 3;

	Item* m_Item = nullptr;

	switch (ItemType)
	{
	case Item::Gold_Coin:

		if (1 <= randCoinItem)
		{
			m_Item = Stage()->Create_Actor<Item>();
			m_Item->Change_ItemImage(L"Potion", Item::Potion);
			break;
		}

		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Gold_Coin", Item::Gold_Coin);
		break;
	case Item::Silver_Coin:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Silver_Coin", Item::Silver_Coin);
		break;
	case Item::Bronze_Coin:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Bronze_Coin", Item::Bronze_Coin);
		break;
	case Item::Gold_CoinPurse:
		if (1 <= randCoinItem)
		{
			m_Item = Stage()->Create_Actor<Item>();
			m_Item->Change_ItemImage(L"Water_Balloon", Item::Bronze_CoinPurse);
			break;
		}
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Gold_CoinPurse", Item::Gold_CoinPurse);
		break;
	case Item::Silver_CoinPurse:
		if (1 <= randCoinItem)
		{
			m_Item = Stage()->Create_Actor<Item>();
			m_Item->Change_ItemImage(L"RollerSkates", Item::RollerSkates);
			break;
		}
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Silver_CoinPurse", Item::Silver_CoinPurse);
		break;
	case Item::Bronze_CoinPurse:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Bronze_CoinPurse", Item::Bronze_CoinPurse);
		break;
	case Item::Water_Balloon:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Water_Balloon", Item::Bronze_CoinPurse);
		break;
	case Item::Potion:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Potion", Item::Potion);
		break;
	case Item::MegaBomb:
		if (2 <= randCoinItem)
		{
			m_Item = Stage()->Create_Actor<Item>();
			m_Item->Change_ItemImage(L"Potion", Item::Potion);
			break;
		}
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"MegaBomb", Item::MegaBomb);
		break;
	case Item::RollerSkates:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"RollerSkates", Item::RollerSkates);
		break;
	/*case Item::Devil:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Devil", Item::Devil);
		break;
	case Item::Radio:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Radio", Item::Radio);
		break;
	case Item::Owl:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Owl", Item::Owl);
		break;
	case Item::Shild:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Shild", Item::Shild);
		break;
	case Item::Spaceship:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Spaceship", Item::Spaceship);
		break;*/
	case Item::Needle:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Needle", Item::Needle);
		break;
	/*case Item::Turtle:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Turtle", Item::Turtle);
		break;*/
	case Item::Sneakers:
		if (1 <= randCoinItem)
		{
			m_Item = Stage()->Create_Actor<Item>();
			m_Item->Change_ItemImage(L"Water_Balloon", Item::Bronze_CoinPurse);
			break;
		}
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Sneakers", Item::Sneakers);
		break;
	/*case Item::Gloves:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Gloves", Item::Gloves);
		break;
	case Item::Super:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Super", Item::Super);
		break;*/
	case Item::RedDevil:
		if (2 <= randCoinItem)
		{
			m_Item = Stage()->Create_Actor<Item>();
			m_Item->Change_ItemImage(L"RollerSkates", Item::RollerSkates);
			break;
		}
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"RedDevil", Item::RedDevil);
		break;
	/*case Item::MonkeySpanner:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"MonkeySpanner", Item::MonkeySpanner);
		break;
	case Item::Spring_Sleeper:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Spring_Sleeper", Item::Spring_Sleeper);
		break;
	case Item::Poison_Potion:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Poison_Potion", Item::Poison_Potion);
		break;
	case Item::Can:
		m_Item = Stage()->Create_Actor<Item>();
		m_Item->Change_ItemImage(L"Can", Item::Can);
		break;*/

		// 아이템 X경우 
	case Item::Emtpy_Item:
	default:
		break;
	}

	// 아이템 생성 X
	if (nullptr == m_Item)
	{
		return;
	}

	m_ItemMap.insert(std::map<__int64, Item*>::value_type(_Index, m_Item));
	m_Item->Pos(ItemPos);
}

void EditorTileMap::Open_ItemData(int _ItemType, F_Position _Pos)
{
	TileMapRenderer::Tile* pTile = m_pTileRenderer->Find_ScreenPosTile(_Pos);

	if (pTile == nullptr)
	{
		return;
	}

	pTile->ItemType = _ItemType;
}


//

void EditorTileMap::OriginBlock_Delete(VECTOR2_INT _Index)
{
	std::map<__int64, ActorObjBase*>::iterator Find_Iter = m_ObjTile.find(_Index);

	if (Find_Iter != m_ObjTile.end())
	{
		Find_Iter->second->Obj_Death();
	}
}

void EditorTileMap::OriginBlockMove_Delete(VECTOR2_INT _Index)
{
	std::map<__int64, ActorObjBase*>::iterator Find_Iter = m_BlockjAni.find(_Index);

	if (Find_Iter != m_BlockjAni.end())
	{
		Find_Iter->second->Obj_Death();
	}

	std::map<__int64, ActorObjBase*>::iterator asdf = m_BlockjAni.find(_Index);
	int a = 0;
}


// 블럭삭제
void EditorTileMap::Erase_ObjIndex(F_Position _Pos)
{
	VECTOR2_INT Index = m_pTileRenderer->OriginTileIndex(_Pos);
	TileMapRenderer::Tile* pTile = m_pTileRenderer->Find_ScreenPosTile(_Pos);

	std::map<__int64, ActorObjBase*>::iterator Find_Iter = m_ObjTile.find(Index);

	if (Find_Iter == m_ObjTile.end())
	{
		return;
	}
	OBJTYPE _Index = (OBJTYPE)pTile->ObjIndex;

	pTile->ObjIndex = -1;
	Delete_ItemType(pTile);
	Find_Iter->second->Obj_Death();
	m_ObjTile.erase(Index);


	VECTOR2_INT AddTileIndex = VECTOR2_INT{ 0, 0 };
	F_Position AddTilePos = F_Position{ 0,0 };
	TileMapRenderer::Tile* pAddTile = nullptr;


	switch (_Index)
	{
	case EditorTileMap::BANIFARM_OBJECT_00:			// 물웅덩이
	{
		AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
		AddTileIndex = AddTileIndex + VECTOR2_INT{ 1,0 };
		AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

		pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

		if (pAddTile == nullptr)
		{
			break;
		}
		pAddTile->ObjIndex = -1;			// 타일 인덱스


		break;
	}
	case EditorTileMap::BANIFARM_OBJECT_02:			// 집
	{

		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 4; x++)
			{
				int a = 0;
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = (VECTOR2_INT)AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_09:			// 딸기 케이크
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_10:			// 블루베리 케이크
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;

			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_11:			// 달콤한 왕배찌
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 4; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_12:			// 너구리 케이크
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_13:			// 커피
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_14:			// 왕도넛
	{
		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::COOKIE_OBJECT_15:			// 왕도넛 2층
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::DESERT_OBJECT_04:			// 야자수 + 물
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::ICE_OBJECT_04:				// 빨간 지붕 집
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::ICE_OBJECT_05:				// 나무집
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::ICE_OBJECT_06:				// 이글루
	{
		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 3; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = OBJTYPE_MAX;
			}
		}
		break;
	}
	case EditorTileMap::PIRATE_OBJECT_05:			// 깃발
	{
		int a = 0;
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 3; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}

		break;
	}
	case EditorTileMap::VILAGE_OBJECT_04:			// 풍차
	{
		// y축 기준
		for (int y = 0; y < 2; y++)
		{
			// x축 기준 
			for (int x = 0; x < 3; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::VILAGE_OBJECT_12:			// 비행기
	{
		// y축 기준
		for (int y = 0; y < 1; y++)
		{
			// x축 기준 
			for (int x = 0; x < 2; x++)
			{
				if (0 >= x && y >= 0)
					continue;

				AddTileIndex = m_pTileRenderer->OriginTileIndex(_Pos);
				AddTileIndex = AddTileIndex + VECTOR2_INT{ x,-y };
				AddTilePos = m_pTileRenderer->OriginTilePos(AddTileIndex);

				pAddTile = m_pTileRenderer->Find_ScreenPosTile(AddTilePos);

				if (pAddTile == nullptr)
				{
					break;
				}
				pAddTile->ObjIndex = -1;
			}
		}
		break;
	}
	case EditorTileMap::NONE:
		break;
	case EditorTileMap::OBJTYPE_MAX:
		break;
	default:
		break;
	}
}


INT_PTR CALLBACK DlgProc(HWND _hwnd, UINT _msg, WPARAM _wpraram, LPARAM _lparam)
{
	switch (_msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
	{
		switch (_wpraram)
		{
		case IDOK:
		{
			GetDlgItemText(_hwnd, IDC_MapName, FileName, 1000);
			EndDialog(_hwnd, _lparam);
			break;
		}
		case IDCANCEL:
		{
			EndDialog(_hwnd, _lparam);
			break;
		}
		default:
			break;
		}

		return TRUE;
	}
	default:
		break;
	}
	return FALSE;
}

AnimationRenderer* EditorTileMap::MoveBoxAnimation(std::wstring _Dir, VECTOR2_INT _Index)
{
	F_Position Pos = m_pTileRenderer->OriginTilePos(_Index);


	if (L"UP" == _Dir)
	{
		ActorObjBase* Obj = nullptr;
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* m_pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		m_pRender->Animation_Create(L"MoveUP", L"Nudge_Box_UP.bmp", 0, 7, false, 0.2f);
		m_pRender->Animation_Create(L"Empty", L"vilage_block_00.bmp", 8, 8, false, 0.1f);
		m_pRender->Animation_Change(L"MoveUP");
		m_pRender->Size(F_Position{ 60 ,140 });
		m_pRender->Pivot(F_Position{ 0.5f,-75.5f });

		return m_pRender;
	}
	else if (L"DOWN" == _Dir)
	{
		ActorObjBase* Obj = nullptr;
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* m_pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		m_pRender->Animation_Create(L"MoveLeft", L"Nudge_Box_DOWN.bmp", 0, 7, false, 0.2f);
		m_pRender->Animation_Create(L"Empty", L"vilage_block_00.bmp", 8, 8, false, 0.2f);
		m_pRender->Pivot(F_Position{ -60.5f, -5.5f });
		m_pRender->Size(F_Position{ 120 ,65 });
		m_pRender->Animation_Change(L"MoveLeft");
		return m_pRender;
	}
	else if (L"LEFT" == _Dir)
	{
		ActorObjBase* Obj = nullptr;
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* m_pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		m_pRender->Animation_Create(L"MoveLeft", L"Nudge_Box_LEFT.bmp", 0, 9, false, 0.2f);
		m_pRender->Animation_Create(L"Empty", L"vilage_block_00.bmp", 8, 8, false, 0.1f);
		m_pRender->Pivot(F_Position{ -60.5f, -5.5f });
		m_pRender->Size(F_Position{ 120 ,65 });
		m_pRender->Animation_Change(L"MoveLeft");
		return m_pRender;
	}
	else if (L"RIGHT" == _Dir)
	{
		ActorObjBase* Obj = nullptr;
		Obj = Stage()->Create_Actor<ObjTile>();
		AnimationRenderer* m_pRender = Obj->Create_Renderer<AnimationRenderer>(11);
		m_pRender->Animation_Create(L"MoveRight", L"Nudge_Box_RIGHT.bmp", 0, 9, false, 0.2f);
		m_pRender->Animation_Create(L"Empty", L"vilage_block_00.bmp", 8, 8, false, 0.2f);
		m_pRender->Pivot(F_Position{ 59.5f,-5.5f });
		m_pRender->Size(F_Position{ 120 ,65 });
		m_pRender->Animation_Change(L"MoveRight");
		return m_pRender;
	}

	return nullptr;
}
