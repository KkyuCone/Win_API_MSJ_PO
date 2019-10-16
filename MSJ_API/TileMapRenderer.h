#pragma once
#include "ObjectRenderer.h"
#include "Render_Vector.h"
#include <map>
#include <string>

class GameObjectMultiSprite;
class TileMapRenderer : public ObjectRenderer
{
public:
	class Tile
	{
	public:
		int TileImageIndex;		// �̹��� ����
		int ObjIndex;			// �̵� ���� ����
		int ItemType;			// ������ Ÿ��

	public:
		Tile& operator= (const Tile& _Other)
		{
			TileImageIndex = _Other.TileImageIndex;

			return *this;
		}
		
	public:
		Tile() : TileImageIndex(0), ObjIndex(-1), ItemType(-1)
		{}
		~Tile() {}
	};

	class OutPutTile
	{
	public:
		VECTOR2_INT Index;		// Ÿ�� �ε��� ����
		Tile TileData;			// Ÿ�� ����
	};

private:
	GameObjectMultiSprite* m_pTileSprite;
	std::map<__int64, Tile*> m_Tile;

public:
	int Get_TileObjData(VECTOR2_INT _Index);


private:
	size_t Set_TileCount();

public:
	size_t Get_SpriteCount();

public:
	void Reset();
	size_t Get_TileCount();
	void Get_TileData(OutPutTile* _Buffer, int _Size);

public:
	void Create_MapTile(const wchar_t* _Name, F_Position _TileSize);
	Tile* SetTile(VECTOR2_INT _Index, int _SpriteIndex = 0);

	void EraseTile(VECTOR2_INT _Index);

	Tile* Set_ScreenPosTile(F_Position _Index, int _SpriteIndex = 0);
	Tile* Find_ScreenPosTile(F_Position _Index);		//ObjIndex�� ������ ã�� (�� �ش���ġ�� Ÿ�ϰ��� -1�ΰ� �� ���� ���ΰ�)
	void Erase_ScreenPosTile(F_Position _Index);


public:
	VECTOR2_INT OriginTileIndex(F_Position _Index);
	F_Position OriginTilePos(F_Position _Index);
	F_Position OriginTilePos(VECTOR2_INT _Index);



public:
	bool Find_BlockTile(VECTOR2_INT _Index);
	int Find_MoveBlockTile(VECTOR2_INT _Index);

	int Find_BlockMove(VECTOR2_INT _Index, std::wstring _Dir);			// �̵������� �� Ȯ�� -> �о��(Ÿ�ϱ�ü)

private:
	void Render() override;



public:
	TileMapRenderer();
	~TileMapRenderer();
};

