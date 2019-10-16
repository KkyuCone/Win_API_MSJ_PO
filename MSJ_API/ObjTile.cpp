#include "stdafx.h"
#include "ObjTile.h"
#include "AnimationRenderer.h"


ObjTile::ObjTile()
{
}


ObjTile::~ObjTile()
{
}

void ObjTile::Start_Update() 
{

}

void ObjTile::Create_ObjTileRender(__int64 _Index, const wchar_t* _ObjAniName, const wchar_t* _ImageFileName)
{
	AnimationRenderer* pRender = Create_Renderer<AnimationRenderer>(10);
	pRender->Animation_Create(_ObjAniName, _ImageFileName, 0, 0);
	pRender->Animation_Change(_ObjAniName);
	pRender->Size({ 54, 62 });
	pRender->Pivot({ 0, -3.0f });

	m_ObjRenderer.insert(std::map<__int64, AnimationRenderer*>::value_type(_Index, pRender));
}

void ObjTile::Get_ObjTileRender()
{

}
