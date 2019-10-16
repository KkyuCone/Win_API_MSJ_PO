#pragma once
#include "ObjectSubBase.h"
#include "Render_Vector.h"
#include <list>
#include <set>

// 충돌체 타입
enum COL_TYPE
{
	COL_RECT,		// 사각형 (x, y, sizex, sizey)
	COL_CIRCLE,		// 원형 (x, y, r)
	COL_POINT,		// 점 ( x, y)
	COL_MAX
};

class ObjectCollision : public ObjectSubBase
{
public:
	std::wstring Name;

private:
	F_Rectangle m_ObjCol;
	COL_TYPE m_ColType;
	std::set<ObjectCollision*>::iterator ColFind_Iter;
	std::set<ObjectCollision*> m_OtherCol;

public:
	void ChangeName(wchar_t* _Name)
	{
		Name = _Name;
	}

public:
	void Set_CollisionType(int _Type)
	{
		m_ColType = (COL_TYPE)_Type;
	}

public:
	void ParentPosSetting();
	bool GeoCheck(ObjectCollision* _OtherCol);

	// 충돌체크함수 ( 다른 Collision과의 충돌관련 함수, 충돌만 생각하기, 충돌관리는 다른곳에서함 )
	void Collision_Check(ObjectCollision* _OtherCol);

	// 지우기
	void OtherCol_Erase(ObjectCollision* _Col);

	// 디버그
	void DebugRender();

public:
	ObjectCollision();
	~ObjectCollision();
};

