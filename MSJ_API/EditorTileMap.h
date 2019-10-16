#pragma once
#include "ActorObjBase.h"
#include "TimerCal.h"
#include "TileMapRenderer.h"
#include <string>

class BoxObjectRenderer;
class SingleRenderer;
class ObjectCollision;
class AnimationRenderer;
class Item;
class EditorTileMap : public ActorObjBase
{
public:
	enum EDITORMODE
	{
		OBJ,
		TILE,
		NOTDESTROY_OBJ,
	};

	enum OBJTYPE
	{
		RUZZI_OBJECT_00,					// ruzzi
		RUZZI_OBJECT_01,
		RUZZI_OBJECT_02,
		RUZZI_OBJECT_03,
		RUZZI_OBJECT_04,
		RUZZI_OBJECT_05,
		RUZZI_OBJECT_06,
		RUZZI_OBJECT_09,
		RUZZI_OBJECT_10,
		RUZZI_OBJECT_11,


		BANIFARM_BLOCK_00,		// ����							// banifarm
		BANIFARM_BLOCK_01,		// ����		
		BANIFARM_BLOCK_02,		// ����		
		BANIFARM_BLOCK_03,		// ����		
		BANIFARM_BLOCK_04,		// ����
		BANIFARM_BLOCK_05,		// ����
		BANIFARM_BLOCK_06,		// ����
		BANIFARM_BLOCK_07,		// ����
		BANIFARM_BLOCK_08,		// ����
		BANIFARM_BLOCK_09,		// ����
		BANIFARM_BLOCK_10,		// ����
		BANIFARM_OBJECT_00,		// �� X : 2
		BANIFARM_OBJECT_02,		// �� X : 3   Y : 2 
		BANIFARM_OBJECT_03,
		BANIFARM_OBJECT_04,
		BANIFARM_TILE_15,
		BANIFARM_TILE_16,
		BANIFARM_TILE_17,
		BANIFARM_TILE_18,
		BANIFARM_TILE_19,
		BANIFARM_TILE_20,
		BANIFARM_TILE_21,
		BANIFARM_TILE_22,
		BANIFARM_TILE_23,

		CAMP_BLOCK_00,			// ����			// camp
		CAMP_BLOCK_01,			// ����
		CAMP_BLOCK_02,			// ����
		CAMP_BLOCK_03,			// ����
		CAMP_BLOCK_04,			// ��鸮�� ����
		CAMP_BLOCK_05,			// ��鸮�� ����
		CAMP_BLOCK_06,			// ���� ���� 1
		CAMP_BLOCK_07,			// ���� ���� 2
		CAMP_BLOCK_08,			// ���� ���� 3
		CAMP_BLOCK_09,			// ���� ���� 4
		CAMP_BLOCK_10,			// ���� ���� 5 (����)
		CAMP_BLOCK_11,
		CAMP_OBJECT_00,			// ��鸮�� ��Ʈ1
		CAMP_OBJECT_01,			// ��鸮�� ��Ʈ2
		CAMP_OBJECT_02,
		CAMP_OBJECT_03,
		CAMP_OBJECT_04,
		CAMP_OBJECT_05,
		CAMP_OBJECT_06,
		CAMP_OBJECT_07,
		CAMP_OBJECT_08,
		CAMP_OBJECT_09,
		CAMP_OBJECT_10,
		CAMP_OBJECT_11,
		CAMP_OBJECT_12,
		CAMP_OBJECT_13,
		CAMP_OBJECT_14,
		CAMP_OBJECT_15,
		CAMP_OBJECT_16,
		CAMP_OBJECT_17,
		CAMP_OBJECT_18,
		CAMP_OBJECT_19,
		CAMP_OBJECT_20,
		CAMP_OBJECT_21,
		CAMP_OBJECT_22,

		COOKIE_BLOCK_00,			// ����			// cookie
		COOKIE_BLOCK_01,			// ����
		COOKIE_BLOCK_02,			// ����
		COOKIE_BLOCK_03,			// ����
		COOKIE_BLOCK_04,			// ����
		COOKIE_BLOCK_05,			// ����
		COOKIE_BLOCK_06,			// ����
		COOKIE_OBJECT_00,
		COOKIE_OBJECT_01,
		COOKIE_OBJECT_02,
		COOKIE_OBJECT_03,
		COOKIE_OBJECT_04,
		COOKIE_OBJECT_05,
		COOKIE_OBJECT_06,
		COOKIE_OBJECT_07,
		COOKIE_OBJECT_08,
		COOKIE_OBJECT_09,			// ����ũ		 X : 2	  Y : 1
		COOKIE_OBJECT_10,			// ����ũ		 X : 2	  Y : 1
		COOKIE_OBJECT_11,			// ������ ����	 X : 4	  Y : 1
		COOKIE_OBJECT_12,			// �ʱ���		 X : 2	  Y : 1
		COOKIE_OBJECT_13,			// ��			 X : 2	  Y : 1
		COOKIE_OBJECT_14,			// �յ���		 X : 2    Y : 2
		COOKIE_OBJECT_15,			// �յ���2��		 X : 2    Y : 1
		COOKIE_TILE_03,


		DESERT_BLOCK_00,			// desert
		DESERT_BLOCK_01,
		DESERT_BLOCK_02,
		DESERT_BLOCK_03,
		DESERT_OBJECT_00,
		DESERT_OBJECT_01,
		DESERT_OBJECT_02,
		DESERT_OBJECT_03,
		DESERT_OBJECT_04,			// ���ڼ�+��		X : 2		Y : 1
		DESERT_OBJECT_05,
		DESERT_OBJECT_06,
		DESERT_OBJECT_07,
		DESERT_OBJECT_08,
		DESERT_OBJECT_09,
		DESERT_OBJECT_10,
		DESERT_OBJECT_11,
		DESERT_OBJECT_12,
		DESERT_OBJECT_13,
		DESERT_OBJECT_14,
		DESERT_OBJECT_15,
		DESERT_OBJECT_16,
		DESERT_OBJECT_17_DUMMY,


		ICE_BLOCK_00,					// ice
		ICE_BLOCK_01,
		ICE_BLOCK_02,
		ICE_BLOCK_03,
		ICE_OBJECT_00,
		ICE_OBJECT_01,
		ICE_OBJECT_02,
		ICE_OBJECT_03,
		ICE_OBJECT_04,			// ����������		X : 2		Y : 1
		ICE_OBJECT_05,			// ������			X : 2		Y : 1
		ICE_OBJECT_06,			// �̱۷�			X : 3		Y : 2
		ICE_OBJECT_07,
		ICE_OBJECT_08,
		ICE_OBJECT_09,
		ICE_OBJECT_10,
		ICE_OBJECT_11,
		ICE_OBJECT_12,
		ICE_OBJECT_13,
		ICE_OBJECT_14,
		ICE_OBJECT_15,
		ICE_OBJECT_16,
		ICE_OBJECT_17,
		ICE_OBJECT_18,
		ICE_OBJECT_19,
		ICE_OBJECT_20,
		ICE_OBJECT_21,
		ICE_OBJECT_22,
		ICE_OBJECT_23,
		ICE_TILE_02,
		ICE_TILE_03,
		ICE_TILE_04,
		ICE_TILE_05,
		ICE_TILE_06,
		ICE_TILE_07,
		ICE_TILE_08,
		ICE_TILE_09,
		ICE_TILE_10,
		ICE_TILE_11,
		ICE_TILE_12,


		PIRATE_BLOCK_00,				// pirate
		PIRATE_BLOCK_01,
		PIRATE_BLOCK_02,
		PIRATE_BLOCK_03,
		PIRATE_BLOCK_04,
		PIRATE_OBJECT_00,
		PIRATE_OBJECT_01,
		PIRATE_OBJECT_02,
		PIRATE_OBJECT_03,
		PIRATE_OBJECT_04,
		PIRATE_OBJECT_05,			// ���			X : 3		Y : 1
		PIRATE_OBJECT_06,
		PIRATE_OBJECT_07,
		PIRATE_OBJECT_08,
		PIRATE_OBJECT_09,
		PIRATE_OBJECT_10,
		PIRATE_OBJECT_11,
		PIRATE_OBJECT_12,
		PIRATE_OBJECT_13,
		PIRATE_OBJECT_14,
		PIRATE_OBJECT_15,
		PIRATE_OBJECT_16,
		PIRATE_OBJECT_17,

		VILAGE_BLOCK_00,		// ����				// vilage
		VILAGE_BLOCK_01,		// ����
		VILAGE_BLOCK_02,		// ����
		VILAGE_BLOCK_03,		// ��鸮�� ����
		VILAGE_OBJECT_00,
		VILAGE_OBJECT_01,
		VILAGE_OBJECT_02,
		VILAGE_OBJECT_03,
		VILAGE_OBJECT_04,		// ǳ��				X :	3		Y : 2
		VILAGE_OBJECT_05,
		VILAGE_OBJECT_12,		// �����			X : 2		Y : 1

		NONE,
		OBJTYPE_MAX
	};


public:
	TileMapRenderer* m_pBlackTile;

	TileMapRenderer* m_pTileRenderer;
	SingleRenderer* m_pSelectTile;

	ObjectCollision* m_pTileCol;


	AnimationRenderer*  m_pObjRenderer;		// ������Ʈ 
	SingleRenderer* m_pSelectObj;



	TimerCal m_FadeTimer;

	float StartDelay;

	EDITORMODE eMode;


	int m_BlackTileIndex;
	int m_TileIndex;
	int m_ObjectIndex;

	float m_TileTime;

	std::map<__int64, ActorObjBase*> m_ObjTile;
	std::map<__int64, ActorObjBase*> m_BlockjAni;

	// ������
	std::map<__int64, Item*> m_ItemMap;

public:
	int Create_ItemType(OBJTYPE _Type);
	void Delete_ItemType(TileMapRenderer::Tile* _Tile);

	void Create_Item(VECTOR2_INT _Index, TileMapRenderer::Tile* _Tile);

	void Open_ItemData(int _ItemType, F_Position _Pos);


public:
	void Start_Update() override;
	void Prev_Update() override;
	void Update() override;
	void Late_Update() override;
	void DebugRender() override;

public:
	void LoadMap();
	void SaveMap();

	void EditorTileDelete();

	void EditorObjDelete();

	void TileUpdate();
	void ObjUpdate();

	// �� ����
	ActorObjBase* CreateObjIndex(OBJTYPE _Index, F_Position Pos);
	ActorObjBase* CreateMoveObjIndex(OBJTYPE _Index, F_Position _Pos, std::wstring);		// �������ڰ����� �����
	// �� ����
	void Erase_ObjIndex(F_Position _Pos);

	// Ÿ��, ������Ʈ ü���� -> Ÿ�� ����
	void Tile_Prev();
	void Tile_Next();
	void Obj_Prev();
	void Obj_Next();


	void ObjectSelect(OBJTYPE _ObjType);


	ActorObjBase* Block_Animation(EditorTileMap::OBJTYPE _Type, F_Position _Pos);
	ActorObjBase* Block_AnimationNoneItem(EditorTileMap::OBJTYPE _Type, F_Position _Pos);
	void OriginBlock_Delete(VECTOR2_INT _Index);
	void OriginBlockMove_Delete(VECTOR2_INT _Index);

private:
	bool m_bEditorMode;

public:
	void EditorMode_On()
	{
		m_bEditorMode = true;
	}

	void EditorMode_Off()
	{
		m_bEditorMode = false;
	}

	bool Get_EditorMode()
	{
		return m_bEditorMode;
	}

	bool AddObjPosCheck(OBJTYPE _ObjType, F_Position _ClickPos);			// �� ��ġ�� �߰� üũ�� �Լ�

	public:
		AnimationRenderer* MoveBoxAnimation(std::wstring _Dir, VECTOR2_INT _Index);



public:
	EditorTileMap();
	~EditorTileMap();
};

