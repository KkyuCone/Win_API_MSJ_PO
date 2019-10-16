#include "stdafx.h"
#include "ObjectCollision.h"
#include "ActorObjBase.h"
#include "GameCoreMath.h"
#include "ResourceManager.h"

///////////////////////////////////////////////////////
ObjectCollision::ObjectCollision()
{
}


ObjectCollision::~ObjectCollision()
{
	std::set<ObjectCollision*>::iterator Col_StartIter = m_OtherCol.begin();
	std::set<ObjectCollision*>::iterator Col_EndIter = m_OtherCol.end();

	for (; Col_StartIter != Col_EndIter; ++Col_StartIter)
	{
		(*Col_StartIter)->OtherCol_Erase(this);
	}
}

///////////////////////////////////////////////////////

void ObjectCollision::ParentPosSetting()
{
	m_ObjCol.Position = ParentPos();
	m_ObjCol.Size = m_Size;
}

bool ObjectCollision::GeoCheck(ObjectCollision* _OtherCol)
{
	switch (m_ColType)
	{
	case COL_RECT:
		switch (_OtherCol->m_ColType)
		{
		case COL_RECT:
			return GameCoreMath::RECT_RECT(m_ObjCol, _OtherCol->m_ObjCol);
		case COL_CIRCLE:
			return GameCoreMath::RECT_CIRCLE(m_ObjCol, _OtherCol->m_ObjCol);
		case COL_POINT:
			return GameCoreMath::RECT_POINT(m_ObjCol, _OtherCol->m_ObjCol.Position);
		default:
			break;
		}
	case COL_CIRCLE:
		switch (_OtherCol->m_ColType)
		{
		case COL_RECT:
			return GameCoreMath::RECT_CIRCLE(_OtherCol->m_ObjCol, m_ObjCol);
		case COL_CIRCLE:
			return GameCoreMath::CIRCLE_CIRCLE(m_ObjCol, _OtherCol->m_ObjCol);
		case COL_POINT:
			return GameCoreMath::CIRCLE_POINT(m_ObjCol, _OtherCol->m_ObjCol.Position);
		default:
			break;
		}
	case COL_POINT:
		switch (_OtherCol->m_ColType)
		{
		case COL_RECT:
			return GameCoreMath::RECT_POINT(_OtherCol->m_ObjCol, m_ObjCol.Position);
		case COL_CIRCLE:
			return GameCoreMath::CIRCLE_POINT(_OtherCol->m_ObjCol, m_ObjCol.Position);
		case COL_POINT:
			return GameCoreMath::POINT_POINT(m_ObjCol, _OtherCol->m_ObjCol);
		default:
			break;
		}
	default:
		return false;
		break;
	}
}

// 충돌체크
void ObjectCollision::Collision_Check(ObjectCollision * _OtherCol)
{
	// 찾기
	ColFind_Iter = m_OtherCol.find(_OtherCol);

	if (true == GeoCheck(_OtherCol))
	{
		if (ColFind_Iter != m_OtherCol.end())
		{
			// 충돌중임
			Object()->Collision_Stay(this, _OtherCol);
			_OtherCol->Object()->Other_Collision_Stay(_OtherCol, this);
		}
		else
		{
			Object()->Collision_Enter(this, _OtherCol);
			_OtherCol->Object()->Other_Collision_Enter(_OtherCol, this);
			m_OtherCol.insert(_OtherCol);
			_OtherCol->m_OtherCol.insert(this);
		}
	}
	else if (ColFind_Iter != m_OtherCol.end())
	{
		// 해제
		Object()->Collision_Exit(this, _OtherCol);
		OtherCol_Erase(_OtherCol);
		_OtherCol->OtherCol_Erase(this);
	}
}


void ObjectCollision::OtherCol_Erase(ObjectCollision* _Col)
{
	ColFind_Iter = m_OtherCol.find(_Col);

	if (ColFind_Iter != m_OtherCol.end())
	{
		m_OtherCol.erase(ColFind_Iter);
	}
}


void ObjectCollision::DebugRender()
{
	F_Rectangle DebugObjCol = m_ObjCol;

	DebugObjCol.Position = ScreenPos();

	// 투명색 넣기
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(BHDC, myBrush);

	switch (m_ColType)
	{
	case COL_RECT:
		Rectangle(BHDC, DebugObjCol.I_Left(), DebugObjCol.I_Top(), DebugObjCol.I_Right(), DebugObjCol.I_Botton());
		break;
	case COL_CIRCLE:
		Ellipse(BHDC, DebugObjCol.I_Left(), DebugObjCol.Position.IntY() - DebugObjCol.Size.Half_IntX(), DebugObjCol.I_Right(), DebugObjCol.Position.IntY() + DebugObjCol.Size.Half_IntX());


		break;
	case COL_POINT:
		DebugObjCol.Size = VECTOR2(6, 6);
		Rectangle(BHDC, DebugObjCol.I_Left(), DebugObjCol.I_Top(), DebugObjCol.I_Right(), DebugObjCol.I_Botton());
		break;
	default:
		break;
	}

	SelectObject(BHDC, oldBrush);
	DeleteObject(myBrush);
}
