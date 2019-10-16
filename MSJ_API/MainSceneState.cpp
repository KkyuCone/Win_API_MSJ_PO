#include "stdafx.h"
#include "MainSceneState.h"
#include "ActorObjBase.h"
#include "SoundControl.h"
#include "resource.h"
#include "ResourceManager.h"

// �����

#ifdef _DEBUG
bool MainSceneState::IsDebugMode = true;
#else
bool MainSceneState::IsDebugMode = false;
#endif

#ifdef _DEBUG
bool MainSceneState::IsDebugColMode = true;
#else
bool MainSceneState::IsDebugColMode = false;
#endif

// ĳ���� Ÿ��
MainSceneState::CharacterType MainSceneState::m_GameChar_Type = CharacterType::Bazzi;

// ����
SoundControl* MainSceneState::m_SoundControlBGM = ResourceManager::Instance().SoundControl_Insert();

// ���̸�
std::wstring MainSceneState::SelectMapName = L"";

///////////////////////////////////////////////

MainSceneState::MainSceneState() : m_bLoading(false)
{
}


MainSceneState::~MainSceneState()
{
	m_ObjStart = m_ObjList.begin();
	m_ObjEnd = m_ObjList.end();

	for (; m_ObjStart != m_ObjEnd; m_ObjStart++)
	{
		if ( nullptr != (*m_ObjStart))
		{
			delete (*m_ObjStart);
			(*m_ObjStart) = nullptr;
		}
	}
}

///////////////////////////////////////////////

void MainSceneState::Prev_Update()
{
	m_ObjStart = m_ObjList.begin();
	m_ObjEnd = m_ObjList.end();

	for (; m_ObjStart != m_ObjEnd; m_ObjStart++)
	{
		(*m_ObjStart)->Prev_Update();
	}
}

void MainSceneState::Update()
{
	m_ObjStart = m_ObjList.begin();
	m_ObjEnd = m_ObjList.end();

	for (; m_ObjStart != m_ObjEnd; m_ObjStart++)
	{
		(*m_ObjStart)->Update();
	}
}

void MainSceneState::Late_Update()
{
	m_ObjStart = m_ObjList.begin();
	m_ObjEnd = m_ObjList.end();

	for (; m_ObjStart != m_ObjEnd; m_ObjStart++)
	{
		(*m_ObjStart)->Late_Update();
	}
}


// ����, ���� (��,�Ѿ� ��)
void MainSceneState::Release()
{
	m_RenderManager.Release();
	m_ColManager.Release();

	m_ObjStart = m_ObjList.begin();
	m_ObjEnd = m_ObjList.end();

	for (; m_ObjStart != m_ObjEnd;) 
	{
		if (false == (*m_ObjStart)->IsObjDeath())
		{
			m_ObjStart++;
			continue;
		}

		delete (*m_ObjStart);
		m_ObjStart = m_ObjList.erase(m_ObjStart);
	}
}


//////////////////////////////////////////////////// Render

void MainSceneState::Obj_Renderer_Insert(int _Key, ObjectRenderer * _pObjRenderer)
{
	Tassert(nullptr == _pObjRenderer);

	m_RenderManager.Renderer_Insert(_Key, _pObjRenderer);
}



void MainSceneState::Obj_Render()
{
	m_RenderManager.Render();

	// �����
	if (true == IsDebugColMode)
	{
		m_ColManager.DebugRender();
	}

	if (true == IsDebugMode)
	{
		m_ObjStart = m_ObjList.begin();
		m_ObjEnd = m_ObjList.end();

		for ( ; m_ObjStart != m_ObjEnd; ++m_ObjStart)
		{
			// ������Ʈ���°� �ƴϸ� ��������Ʈ��
			if (false == (*m_ObjStart)->IsObjUpdate())
			{
				continue;
			}
			(*m_ObjStart)->DebugRender();
		}
	}
}


// YSorting
void MainSceneState::YSort_On(int _YValue)
{
	m_RenderManager.YSort_On(_YValue);
}




////////////////////////////////////////// Collision

void MainSceneState::Insert_Collision(const wchar_t * _GroupName, ObjectCollision * _pObjCollision)
{
	m_ColManager.Insert_Collision(_GroupName, _pObjCollision);
}

void MainSceneState::Collision_Link(const wchar_t * _Left, const wchar_t * _Right)
{
	m_ColManager.Link(_Left, _Right);
}


void MainSceneState::Obj_Collision()
{
	m_ColManager.Collision_Update();
}