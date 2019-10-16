#include "stdafx.h"
#include "ActorObjBase.h"
#include "ObjectRenderer.h"
#include "ObjectCollision.h"

///////////////////////////////////////////////////////

ActorObjBase::ActorObjBase() : m_ScaleRatio(1.0f)
{
}


ActorObjBase::~ActorObjBase()
{
	// 렌더
	std::list<ObjectRenderer*>::iterator Start_Iter = m_pObjectRendererList.begin();
	std::list<ObjectRenderer*>::iterator End_Iter = m_pObjectRendererList.end();

	for (; Start_Iter != End_Iter; Start_Iter++)
	{
		delete (*Start_Iter);
	}

	// 충돌
	std::list<ObjectCollision*>::iterator Col_StartIter = m_pCollisionList.begin();
	std::list<ObjectCollision*>::iterator Col_EndIter = m_pCollisionList.end();

	for (; Col_StartIter != Col_EndIter; ++Col_StartIter)
	{
		delete (*Col_StartIter);
	}
}


////////////////////////////////////////////////////////


void ActorObjBase::Prev_Update()
{
}

void ActorObjBase::Update()
{
}

void ActorObjBase::Late_Update()
{
}



// CameraPos
F_Position ActorObjBase::ScreenPos()
{
	return m_BasePos - Stage()->CameraPos();
}


/////////////////////////////////////////////////// 충돌

ObjectCollision * ActorObjBase::Create_Collision(const wchar_t * _GroupName, int _Type)
{
	ObjectCollision* NewCollision = new ObjectCollision();
	NewCollision->Set_CollisionType(_Type);
	NewCollision->Object(this);
	m_pCollisionList.push_back(NewCollision);
	Stage()->Insert_Collision(_GroupName, NewCollision);

	return NewCollision;
}


//////////////////////////////////////////////// 디버그
void ActorObjBase::DebugRender()
{

}