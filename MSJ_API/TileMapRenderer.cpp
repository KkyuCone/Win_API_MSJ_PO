#include "stdafx.h"
#include "TileMapRenderer.h"
#include "GameObjectMultiSprite.h"
#include "ResourceManager.h"
#include "ActorObjBase.h"
#include "EditorTileMap.h"



//////////////////////////////////////////////////////
TileMapRenderer::TileMapRenderer()
{
}


TileMapRenderer::~TileMapRenderer()
{
	Reset();
}

////////////////////////////////////////////////////////// Tile


// 이동시 블럭 찾기
bool TileMapRenderer::Find_BlockTile(VECTOR2_INT _Index)
{
	std::map<__int64, Tile*>::iterator Tile_Iter = m_Tile.find(_Index);

	if (Tile_Iter != m_Tile.end())
	{
		EditorTileMap::OBJTYPE ObjIndex = (EditorTileMap::OBJTYPE)Tile_Iter->second->ObjIndex;

		// 예외
		switch (ObjIndex)
		{
		case EditorTileMap::CAMP_BLOCK_04:
		case EditorTileMap::CAMP_BLOCK_05:
		case EditorTileMap::CAMP_OBJECT_00:
		case EditorTileMap::CAMP_OBJECT_01:
		case EditorTileMap::VILAGE_BLOCK_03:
			return true;
		default:
			break;
		}

		if (Tile_Iter->second->ObjIndex > -1)
		{
			return false;		// 갈 수 없는 타일
		}
	}

	return true;
}

// 이동시 움직일 수 있는 블럭이 있으면 이동시키기
int TileMapRenderer::Find_BlockMove(VECTOR2_INT _Index, std::wstring _Dir)
{
	std::map<__int64, Tile*>::iterator Tile_Iter = m_Tile.find(_Index);

	if (Tile_Iter != m_Tile.end())
	{
		if (Tile_Iter->second->ObjIndex <= -1)
		{
			return -2;
		}

		EditorTileMap::OBJTYPE ObjIndex = (EditorTileMap::OBJTYPE)Tile_Iter->second->ObjIndex;


		if (L"UP" == _Dir)
		{
			_Index = (VECTOR2_INT)_Index + VECTOR2_INT{ 0, -1 };
		}
		else if (L"DOWN" == _Dir)
		{
			_Index = (VECTOR2_INT)_Index + VECTOR2_INT{ 0, 1 };
		}
		else if (L"LEFT" == _Dir)
		{
			_Index = (VECTOR2_INT)_Index + VECTOR2_INT{ -1, 0 };
		}
		else if (L"RIGHT" == _Dir)
		{
			_Index = (VECTOR2_INT)_Index + VECTOR2_INT{ 1, 0 };
		}
		else
		{
			return -2;			// 상하좌우가 아니라면 나가기
		}

		if (_Index.X < 0 || _Index.Y < 0 ||
			_Index.X >= 12 || _Index.Y >= 14)
		{
			return -2;
		}


		std::map<__int64, Tile*>::iterator ObjMove_Iter = m_Tile.find(_Index);

		if (ObjMove_Iter == m_Tile.end())
		{
			return -2;
		}


		int PossibleMoveObjTile = ObjMove_Iter->second->ObjIndex;

		if (0 <= PossibleMoveObjTile)
		{
			return -2;
		}


		switch (ObjIndex)
		{
		case EditorTileMap::VILAGE_BLOCK_00:				// Vilage 나무상자
			ObjMove_Iter->second->ObjIndex = Tile_Iter->second->ObjIndex;			// 밀어내기 (해당타일 못가기)
			Tile_Iter->second->ObjIndex = -1;										// 밀어낸자리 -> 플레이어들이 이동가능한 타일로 교체

			return ObjIndex;
			break;
		default:
			break;
		}
	}

	return -2;
}

int TileMapRenderer::Find_MoveBlockTile(VECTOR2_INT _Index)
{
	std::map<__int64, Tile*>::iterator Tile_Iter = m_Tile.find(_Index);

	int ObjIndex = -10;

	if (Tile_Iter != m_Tile.end())
	{
		ObjIndex = Tile_Iter->second->ObjIndex;

		switch (ObjIndex)
		{
		case 38:
		case 39:
		case 46:
		case 47:
		case 96:
			return ObjIndex;
		default:
			break;
		}
	}

	return ObjIndex;
}

TileMapRenderer::Tile * TileMapRenderer::SetTile(VECTOR2_INT _Index, int _SpriteIndex)
{
	std::map<__int64, Tile*>::iterator Find_Iter = m_Tile.find(_Index);

	if (Find_Iter != m_Tile.end())
	{
		Find_Iter->second->TileImageIndex = _SpriteIndex;
		return Find_Iter->second;
	}

	Tile* pNewTile = new Tile();
	pNewTile->TileImageIndex = _SpriteIndex;
	m_Tile.insert(std::map<__int64, Tile*>::value_type(_Index, pNewTile));


	return pNewTile;
}

void TileMapRenderer::EraseTile(VECTOR2_INT _Index)
{
	std::map<__int64, Tile*>::iterator Find_Iter = m_Tile.find(_Index);

	if (Find_Iter == m_Tile.end())
	{
		return;
	}

	delete Find_Iter->second;
	m_Tile.erase(Find_Iter);

	return;
}

TileMapRenderer::Tile * TileMapRenderer::Set_ScreenPosTile(F_Position _Index, int _SpriteIndex)
{
	_Index += Object()->Stage()->CameraPos();
	_Index -= m_Pivot;		// 이동한 위치만큼 빼기

	VECTOR2_INT PositionIndex = { (int)(_Index.X / m_Size.X), (int)(_Index.Y / m_Size.Y) };

	if ((14 <= PositionIndex.X || 0 > PositionIndex.X)
		|| (12 <= PositionIndex.Y || 0 > PositionIndex.Y))
	{
		return nullptr;
	}

	return SetTile(PositionIndex, _SpriteIndex);
}

TileMapRenderer::Tile* TileMapRenderer::Find_ScreenPosTile(F_Position _Index)
{
	_Index += Object()->Stage()->CameraPos();
	_Index -= m_Pivot;		// 이동한 위치만큼 빼기

	VECTOR2_INT PositionIndex = { (int)(_Index.X / m_Size.X), (int)(_Index.Y / m_Size.Y) };

	if ((14 <= PositionIndex.X || 0 > PositionIndex.X)
		|| (12 <= PositionIndex.Y || 0 > PositionIndex.Y))
	{
		return nullptr;
	}

	std::map<__int64, Tile*>::iterator Find_Iter = m_Tile.find(PositionIndex);

	if (Find_Iter != m_Tile.end())
	{
		return Find_Iter->second;
	}

	return nullptr;
}



void TileMapRenderer::Erase_ScreenPosTile(F_Position _Index)
{
	_Index += Object()->Stage()->CameraPos();
	_Index -= m_Pivot;		// 이동한 위치만큼 빼기

	VECTOR2_INT PositionIndex = { (int)(_Index.X / m_Size.X), (int)(_Index.Y / m_Size.Y) };

	if ((14 <= PositionIndex.X || 0 > PositionIndex.X)
		|| (12 <= PositionIndex.Y || 0 > PositionIndex.Y))
	{
		return;
	}

	EraseTile(PositionIndex);

	return;
}


VECTOR2_INT TileMapRenderer::OriginTileIndex(F_Position _Index) {
	_Index += Object()->Stage()->CameraPos();
	_Index -= m_Pivot;		// 이동한 위치만큼 빼기

	// _Index.X > 756 || _Index.Y > 660
	if (_Index.X < -5 || _Index.Y < -5 ||_Index.X > 750 || _Index.Y > 650 )
	{
 		return VECTOR2_INT{ -1, -1 };
	}

	VECTOR2_INT PositionIndex = { (int)(_Index.X / m_Size.X), (int)(_Index.Y / m_Size.Y) };

	int b = 0;

	if ((14 <= PositionIndex.X || 0 > PositionIndex.X)
		|| (12 <= PositionIndex.Y || 0 > PositionIndex.Y))
	{
		return VECTOR2_INT{ -1, -1 };
	}

	int c = 0;

	return PositionIndex;
}

F_Position TileMapRenderer::OriginTilePos(F_Position _Index)
{
	_Index += Object()->Stage()->CameraPos();
	_Index -= m_Pivot;		// 이동한 위치만큼 빼기

	VECTOR2_INT PositionIndex = { (int)(_Index.X / m_Size.X), (int)(_Index.Y / m_Size.Y) };

	F_Position _ReturnPos;

	_ReturnPos.X = (int)(PositionIndex.X * m_Size.X) + m_Pivot.X + m_Size.Half_FloatX();
	_ReturnPos.Y = (int)(PositionIndex.Y * m_Size.Y) + m_Pivot.Y + m_Size.Half_FloatY();

	return _ReturnPos;
}


F_Position TileMapRenderer::OriginTilePos(VECTOR2_INT _Index)
{
	F_Position RetrunPos;

	RetrunPos.X = (int)(_Index.X * m_Size.X) + m_Pivot.X + m_Size.Half_FloatX();
	RetrunPos.Y = (int)(_Index.Y * m_Size.Y) + m_Pivot.Y + m_Size.Half_FloatY();

	return RetrunPos;

}


///////////////////////////////////////////////////////////////   TileMapRenderer

void TileMapRenderer::Create_MapTile(const wchar_t * _Name, F_Position _TileSize)
{
	m_pTileSprite = ResourceManager::Instance().Find_MultiSprite(_Name);
	m_Size = _TileSize;
}

size_t TileMapRenderer::Set_TileCount()
{
	return m_pTileSprite->SpriteCount();
}

void TileMapRenderer::Render()
{
	std::map<__int64, Tile*>::iterator Start_Iter = m_Tile.begin();
	std::map<__int64, Tile*>::iterator End_Iter = m_Tile.end();
	
	VECTOR2_INT Position;

	for (; Start_Iter != End_Iter; ++Start_Iter)
	{
		// 프레임워크나 랜더링구조에 대해서 
		// 타일 위치
		Position = Start_Iter->first;
		Position.X = (int)((Position.X * m_Size.X) + m_Pivot.X);
		Position.Y = (int)((Position.Y * m_Size.Y) + m_Pivot.Y);

		if (true == m_bCamera)
		{
			Position -= Object()->Stage()->CameraPos();
		}

		GameObjectSprite* TileSprite = m_pTileSprite->GetSprite(Start_Iter->second->TileImageIndex);

		TransparentBlt(ResourceManager::Instance().BackBufferDC(),
			Position.X,
			Position.Y,
			(int)(m_Size.X),
			(int)(m_Size.Y),
			TileSprite->ObjectImageDC(),
			TileSprite->Pos().IntX(),
			TileSprite->Pos().IntY(),
			TileSprite->Size().IntX(),
			TileSprite->Size().IntY(),
			TileSprite->TransColor()
		);
	}
}

////////////////////////

void TileMapRenderer::Reset()
{
	std::map<__int64, Tile*>::iterator Start_Iter = m_Tile.begin();
	std::map<__int64, Tile*>::iterator End_Iter = m_Tile.end();

	for (; Start_Iter != End_Iter; ++Start_Iter)
	{
		delete Start_Iter->second;
	}

	m_Tile.clear();
}

size_t TileMapRenderer::Get_TileCount()
{
	return m_Tile.size();
}

void TileMapRenderer::Get_TileData(OutPutTile* _Buffer, int _Size)
{
	std::map<__int64, Tile*>::iterator Start_Iter = m_Tile.begin();
	std::map<__int64, Tile*>::iterator End_Iter = m_Tile.end();

	int TileCount = 0;

	for (; Start_Iter != End_Iter; ++Start_Iter)
	{
		_Buffer[TileCount].Index = Start_Iter->first;
		_Buffer[TileCount].TileData = *Start_Iter->second;
		_Buffer[TileCount].TileData.ObjIndex = Start_Iter->second->ObjIndex;
		_Buffer[TileCount].TileData.ItemType = Start_Iter->second->ItemType;

		++TileCount;

		// 범위를 벗어나면 빠져나감
		if (TileCount >= _Size)
		{
			break;
		}
	}
}


// 추가

size_t TileMapRenderer::Get_SpriteCount()
{
	return m_pTileSprite->SpriteCount();
}


int TileMapRenderer::Get_TileObjData(VECTOR2_INT _Index)
{
	std::map<__int64, Tile*>::iterator Find_Iter = m_Tile.find(_Index);


	if (Find_Iter == m_Tile.end())
	{
		return -2;	// 해당 타일이 없다.
	}

	return Find_Iter->second->ObjIndex;
}
