#pragma once
#include "ObjectSubBase.h"
#include "Render_Vector.h"
#include <list>
#include <set>

// �浹ü Ÿ��
enum COL_TYPE
{
	COL_RECT,		// �簢�� (x, y, sizex, sizey)
	COL_CIRCLE,		// ���� (x, y, r)
	COL_POINT,		// �� ( x, y)
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

	// �浹üũ�Լ� ( �ٸ� Collision���� �浹���� �Լ�, �浹�� �����ϱ�, �浹������ �ٸ��������� )
	void Collision_Check(ObjectCollision* _OtherCol);

	// �����
	void OtherCol_Erase(ObjectCollision* _Col);

	// �����
	void DebugRender();

public:
	ObjectCollision();
	~ObjectCollision();
};

