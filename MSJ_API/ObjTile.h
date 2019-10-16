#pragma once
#include "ActorObjBase.h"
#include <map>

class AnimationRenderer;
class ObjTile : public ActorObjBase
{


private:
	std::map<__int64, AnimationRenderer*> m_ObjRenderer;

public:
	void Create_ObjTileRender(__int64 _Index, const wchar_t* _ObjAniName,const wchar_t* _ImageFileName);
	void Get_ObjTileRender();


public:
	void Start_Update() override;

public:
	ObjTile();
	~ObjTile();
};

