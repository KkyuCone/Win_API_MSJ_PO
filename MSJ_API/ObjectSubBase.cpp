#include "stdafx.h"
#include "ObjectSubBase.h"
#include "ActorObjBase.h"

/////////////////////////////////////////////////
ObjectSubBase::ObjectSubBase()
{
}


ObjectSubBase::~ObjectSubBase()
{
}

/////////////////////////////////////////////////

bool ObjectSubBase::IsObjDeath()
{
	return true == ObjUpdateBase::IsObjDeath() || true == Object()->IsObjDeath();
}

bool ObjectSubBase::IsObjUpdate()
{
	return true == ObjUpdateBase::IsObjUpdate() || true == Object()->IsObjUpdate();
}

F_Position ObjectSubBase::ParentPos()
{
	return Object()->Pos() + m_Pivot;
}

F_Position ObjectSubBase::ScreenPos()
{
	return Object()->ScreenPos() + m_Pivot;
}