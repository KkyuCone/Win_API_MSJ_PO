#include "stdafx.h"
#include "Bubble.h"
#include "AnimationRenderer.h"
#include "ObjectCollision.h"
#include "TileMapRenderer.h"
#include "SoundControl.h"

void Bubble::Idle()
{
	bool BubbleUp = true;
	bool BubbleDown = true;
	bool BubbleLeft = true;
	bool BubbleRight = true;

	if (true == m_BombTimer.TimerCheck())
	{
		m_BombTimer.TimerReset();
		Bubble_ChangeState(L"Bomb_Mid");

		//int BubbleUpValue = -1;
		//int BubbleDownValue = -1;
		//int BubbleLeftValue = -1;
		//int BubbleRightValue = -1;
		for (int i = 1; i < m_BubblePower+1; ++i)
		{
			bool GenBubbleUp = false;
			bool GenBubbleDown = false;
			bool GenBubbleLeft = false;
			bool GenBubbleRight = false;

			Bubble* pNewBubble_Top = Stage()->Create_Actor<Bubble>();
			Bubble* pNewBubble_Down = Stage()->Create_Actor<Bubble>();
			Bubble* pNewBubble_Left = Stage()->Create_Actor<Bubble>();
			Bubble* pNewBubble_Right = Stage()->Create_Actor<Bubble>();

			pNewBubble_Top->Pos(m_BasePos + (VECTOR2::UP * (53.0f * i)));
			pNewBubble_Down->Pos(m_BasePos + (VECTOR2::DOWN * ( 53.0f * i)));
			pNewBubble_Left->Pos(m_BasePos + (VECTOR2::LEFT * ( 53.0f * i)));
			pNewBubble_Right->Pos(m_BasePos + (VECTOR2::RIGHT * ( 53.0f * i )));

			// 인덱스 알아오기
			m_BubbleUpIndex = m_TileRenderer->OriginTileIndex(pNewBubble_Top->Pos());
			m_BubbleDownIndex = m_TileRenderer->OriginTileIndex(pNewBubble_Down->Pos());
			m_BubbleLeftIndex = m_TileRenderer->OriginTileIndex(pNewBubble_Left->Pos());
			m_BubbleRightIndex = m_TileRenderer->OriginTileIndex(pNewBubble_Right->Pos());

			int ObjTile_Up = -2;
			int ObjTile_Down = -2;
			int ObjTile_Left = -2;
			int ObjTile_Right = -2;

			if (true == BubbleUp && (m_BubbleUpIndex.X > -1 && m_BubbleUpIndex > -1))
			{
				ObjTile_Up = m_TileRenderer->Get_TileObjData(m_BubbleUpIndex);
				GenBubbleUp = true;
			}

			if (true == BubbleDown && (m_BubbleDownIndex.X > -1 && m_BubbleDownIndex > -1))
			{
				ObjTile_Down = m_TileRenderer->Get_TileObjData(m_BubbleDownIndex);
				GenBubbleDown = true;
			}

			if (true == BubbleLeft && (m_BubbleLeftIndex.X > -1 && m_BubbleLeftIndex > -1))
			{
				ObjTile_Left = m_TileRenderer->Get_TileObjData(m_BubbleLeftIndex);
				GenBubbleLeft = true;
			}

			if (true == BubbleRight && (m_BubbleRightIndex.X > -1 && m_BubbleRightIndex > -1))
			{
				ObjTile_Right = m_TileRenderer->Get_TileObjData(m_BubbleRightIndex);
				GenBubbleRight = true;
			}

			//ObjTile_Up = m_TileRenderer->Get_TileObjData(m_BubbleUpIndex);
			//ObjTile_Down = m_TileRenderer->Get_TileObjData(m_BubbleDownIndex);
			//ObjTile_Left = m_TileRenderer->Get_TileObjData(m_BubbleLeftIndex);
			//ObjTile_Right = m_TileRenderer->Get_TileObjData(m_BubbleRightIndex);

			if (true == BubbleUp)
			{
				if (ObjTile_Up == -1)
				{
					pNewBubble_Top->Bubble_ChangeState(L"Bomb_Top");
				}
				else
				{
					BubbleUp = false;
					BubbleUpValue = i;
					pNewBubble_Top->Bubble_ChangeState(L"Bubble_Empty");
				}
			}
			else
			{
				pNewBubble_Top->Bubble_ChangeState(L"Bubble_Empty");
			}


			if (true == BubbleDown)
			{

				if (ObjTile_Down == -1)
				{
					pNewBubble_Down->Bubble_ChangeState(L"Bomb_Down");
				}
				else
				{
					BubbleDown = false;
					BubbleDownValue = i;
					pNewBubble_Down->Bubble_ChangeState(L"Bubble_Empty");
				}
			}
			else
			{
				pNewBubble_Down->Bubble_ChangeState(L"Bubble_Empty");
			}


			if (true == BubbleLeft)
			{
				if (ObjTile_Left == -1)
				{
					pNewBubble_Left->Bubble_ChangeState(L"Bomb_Left");
				}
				else
				{
					BubbleLeft = false;
					BubbleLeftValue = i;
					pNewBubble_Left->Bubble_ChangeState(L"Bubble_Empty");
				}
			}
			else
			{
				pNewBubble_Left->Bubble_ChangeState(L"Bubble_Empty");
			}


			if (true == BubbleRight)
			{
				if (ObjTile_Right == -1)
				{
					pNewBubble_Right->Bubble_ChangeState(L"Bomb_Right");
				}
				else
				{
					BubbleRight = false;
					BubbleRightValue = i;
					pNewBubble_Right->Bubble_ChangeState(L"Bubble_Empty");
				}
			}
			else
			{
				pNewBubble_Right->Bubble_ChangeState(L"Bubble_Empty");
			}

			//pNewBubble_Top->Bubble_ChangeState(L"Bomb_Top");
			//pNewBubble_Down->Bubble_ChangeState(L"Bomb_Down");
			//pNewBubble_Left->Bubble_ChangeState(L"Bomb_Left");
			//pNewBubble_Right->Bubble_ChangeState(L"Bomb_Right");

			pNewBubble_Top->m_BubbleState = OTHER;
			pNewBubble_Down->m_BubbleState = OTHER;
			pNewBubble_Left->m_BubbleState = OTHER;
			pNewBubble_Right->m_BubbleState = OTHER;

			m_pBubbleBomb.push_back(pNewBubble_Top);
			m_pBubbleBomb.push_back(pNewBubble_Down);
			m_pBubbleBomb.push_back(pNewBubble_Left);
			m_pBubbleBomb.push_back(pNewBubble_Right);

			pNewBubble_Top->m_TileMap = m_TileMap;
			pNewBubble_Down->m_TileMap = m_TileMap;
			pNewBubble_Left->m_TileMap = m_TileMap;
			pNewBubble_Right->m_TileMap = m_TileMap;

			pNewBubble_Top->m_TileRenderer = m_TileRenderer;
			pNewBubble_Down->m_TileRenderer = m_TileRenderer;
			pNewBubble_Left->m_TileRenderer = m_TileRenderer;
			pNewBubble_Right->m_TileRenderer = m_TileRenderer;



			// 상자 터트리기 
			// 위치

			if (true == GenBubbleUp)
			{
				VECTOR2_INT Index_Top = m_TileRenderer->OriginTileIndex(pNewBubble_Top->Pos());
				std::map<__int64, ActorObjBase*>::iterator Find_Iter_Top = m_TileMap->m_ObjTile.find(Index_Top);
				TileMapRenderer::Tile* pTile_Top = m_TileMap->m_pTileRenderer->Find_ScreenPosTile(pNewBubble_Top->Pos());

				if (Find_Iter_Top != m_TileMap->m_ObjTile.end())
				{
					EditorTileMap::OBJTYPE BoxType = (EditorTileMap::OBJTYPE)pTile_Top->ObjIndex;

					if (BoxType >= EditorTileMap::OBJTYPE::RUZZI_OBJECT_00)
					{
						Block_Col_Animation(BoxType, pNewBubble_Top->Pos());
					}
				}

				pNewBubble_Top->pObjCol->ChangeName(L"Bomb");
			}
			else
			{
				pNewBubble_Top->pObjCol->Obj_Death();
			}

			if (true == GenBubbleDown)
			{
				VECTOR2_INT Index_Down = m_TileRenderer->OriginTileIndex(pNewBubble_Down->Pos());
				std::map<__int64, ActorObjBase*>::iterator Find_Iter_Down = m_TileMap->m_ObjTile.find(Index_Down);
				TileMapRenderer::Tile* pTile_Down = m_TileMap->m_pTileRenderer->Find_ScreenPosTile(pNewBubble_Down->Pos());

				if (Find_Iter_Down != m_TileMap->m_ObjTile.end())
				{
					EditorTileMap::OBJTYPE BoxType = (EditorTileMap::OBJTYPE)pTile_Down->ObjIndex;
					if (BoxType >= EditorTileMap::OBJTYPE::RUZZI_OBJECT_00)
					{
						Block_Col_Animation(BoxType, pNewBubble_Down->Pos());
					}
				}

				pNewBubble_Down->pObjCol->ChangeName(L"Bomb");
			}
			else
			{
				pNewBubble_Down->pObjCol->Obj_Death();
			}

			if (true == GenBubbleLeft)
			{
				VECTOR2_INT Index_Left = m_TileRenderer->OriginTileIndex(pNewBubble_Left->Pos());
				std::map<__int64, ActorObjBase*>::iterator Find_Iter_Left = m_TileMap->m_ObjTile.find(Index_Left);
				TileMapRenderer::Tile* pTile_Left = m_TileMap->m_pTileRenderer->Find_ScreenPosTile(pNewBubble_Left->Pos());

				if (Find_Iter_Left != m_TileMap->m_ObjTile.end())
				{
					EditorTileMap::OBJTYPE BoxType = (EditorTileMap::OBJTYPE)pTile_Left->ObjIndex;
					if (BoxType >= EditorTileMap::OBJTYPE::RUZZI_OBJECT_00)
					{
						Block_Col_Animation(BoxType, pNewBubble_Left->Pos());
					}
				}
				pNewBubble_Left->pObjCol->ChangeName(L"Bomb");
			}
			else
			{
				pNewBubble_Left->pObjCol->Obj_Death();
			}

			if (true == GenBubbleRight)
			{
				VECTOR2_INT Index_Right = m_TileRenderer->OriginTileIndex(pNewBubble_Right->Pos());
				std::map<__int64, ActorObjBase*>::iterator Find_Iter_Right = m_TileMap->m_ObjTile.find(Index_Right);
				TileMapRenderer::Tile* pTile_Right = m_TileMap->m_pTileRenderer->Find_ScreenPosTile(pNewBubble_Right->Pos());

				if (Find_Iter_Right != m_TileMap->m_ObjTile.end())
				{
					EditorTileMap::OBJTYPE BoxType = (EditorTileMap::OBJTYPE)pTile_Right->ObjIndex;
					if (BoxType >= EditorTileMap::OBJTYPE::RUZZI_OBJECT_00)
					{
						Block_Col_Animation(BoxType, pNewBubble_Right->Pos());
					}
				}

				pNewBubble_Right->pObjCol->ChangeName(L"Bomb");
			}
			else
			{
				pNewBubble_Right->pObjCol->Obj_Death();
			}


			// 충돌
			pObjCol->ChangeName(L"Bomb");
			//pNewBubble_Top->pObjCol->ChangeName(L"Bomb");
			//pNewBubble_Down->pObjCol->ChangeName(L"Bomb");
			//pNewBubble_Left->pObjCol->ChangeName(L"Bomb");
			//pNewBubble_Right->pObjCol->ChangeName(L"Bomb");
		}
		m_SoundControl->Sound_NewPlayItem(L"BubbleBomb.ogg");
		m_SoundControl->Sound_SetPitch(1.0f);

		m_BubbleState = BOMB;
	}
}

void Bubble::Bomb()
{

	if (true == m_FadeTimer.TimerCheck())
	{
		for (int i = 0; i < ((int)m_pBubbleBomb.size()/4); ++i)
		{
			if (i < BubbleUpValue-2)
			{
				m_pBubbleBomb[(i * 4)]->Bubble_ChangeState(L"Fade_Top");
			}
			else
			{
				m_pBubbleBomb[(i * 4)]->Bubble_ChangeState(L"Bubble_Empty");
			}

			if (i < BubbleDownValue - 2)
			{
				m_pBubbleBomb[(i * 4) + 1]->Bubble_ChangeState(L"Fade_Down");
			}
			else
			{
				m_pBubbleBomb[(i * 4) + 1]->Bubble_ChangeState(L"Bubble_Empty");
			}

			if (i < BubbleLeftValue - 2)
			{
				m_pBubbleBomb[(i * 4) + 2]->Bubble_ChangeState(L"Fade_Left");
			}
			else
			{
				m_pBubbleBomb[(i * 4) + 2]->Bubble_ChangeState(L"Bubble_Empty");
			}

			if (i < BubbleRightValue - 2)
			{
				m_pBubbleBomb[(i * 4) + 3]->Bubble_ChangeState(L"Fade_Right");
			}
			else
			{
				m_pBubbleBomb[(i * 4) + 3]->Bubble_ChangeState(L"Bubble_Empty");
			}

			//m_pBubbleBomb[(i * 4)]->Bubble_ChangeState(L"Fade_Top");
			//m_pBubbleBomb[(i * 4) + 1]->Bubble_ChangeState(L"Fade_Down");
			//m_pBubbleBomb[(i * 4) + 2]->Bubble_ChangeState(L"Fade_Left");
			//m_pBubbleBomb[(i * 4) + 3]->Bubble_ChangeState(L"Fade_Right");
		}

		m_BubbleState = FADE;
	}
}

void Bubble::Fade()
{

	for (size_t i = 0; i < m_pBubbleBomb.size(); ++i)
	{
		Bubble_ChangeState(L"Bubble_Empty");
		if (true == m_pBubbleBomb[i]->m_pTestAniRenderer->IsEndAnimation())
		{
			if (m_pBubbleBomb[i] == m_pBubbleBomb.back())
			{
				m_BubbleState = DEATH;
			}

			m_pBubbleBomb[i]->Bubble_ChangeState(L"Bubble_Empty");
		}
	}

}

void Bubble::Bubble_Death()
{
	if (m_pBubbleBomb.size() <= 0)
	{
		Obj_Death();
		return;
	}

	for ( ; m_pBubbleBomb.size() != 0 ;)
	{
		m_pBubbleBomb.back()->Obj_Death();
		m_pBubbleBomb.pop_back();
	}

}


void Bubble::Block_Col_Animation(EditorTileMap::OBJTYPE _Type, F_Position _Pos)
{
	m_TileMap->Block_Animation(_Type, _Pos);
}

