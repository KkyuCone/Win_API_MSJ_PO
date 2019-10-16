#include "stdafx.h"
#include "EditorStage.h"
#include "EditorTileMap.h"
#include "EditorExit.h"
#include "TileMapRenderer.h"
#include "PlayBackGround.h"

// 내가 추가한것
#include "Util_Core.h"
#include "ObjectCollision.h"
#include "GameMouseCursor.h"

float EditorStage::m_StartTime = 0.0f;

//////////////////////////////////////////////////

EditorStage::EditorStage()
{
	Util_Core::Instance().Change_SceneSize(1024, 768);
}


EditorStage::~EditorStage()
{
}

bool EditorStage::IsStart() 
{
	return 0 >= m_StartTime;
}

//////////////////////////////////////////////////

void EditorStage::Start_Update()
{
	m_StartTime -= TimeManager::Instance().DeltaTime();
}

void EditorStage::Change_Scene_Start() 
{
	m_StartTime = 0.3f;
}

void EditorStage::End_Debug_Update()
{
}

void EditorStage::Loading()
{
	YSort_On(10);
	EditorTileMap* pNewTileMap = Create_Actor<EditorTileMap>();

	for (int y = 0; y < 12; ++y)
	{
		for (int x = 0; x < 14; x++)
		{
			//pNewTileMap->m_pBlackTile->SetTile({ x, y });
			pNewTileMap->m_pTileRenderer->SetTile({ x, y });
		}
	}

	Create_Actor<PlayBackGround>();
	Create_Actor<GameMouseCursor>();
	EditorExit* GameEditorExit = Create_Actor<EditorExit>();
}