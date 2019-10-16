#include "stdafx.h"
#include "RenderManager.h"
#include "ObjectRenderer.h"
#include "ActorObjBase.h"


// �����Լ� Ysorting
bool YSortFunc(const ObjectRenderer* _Left, const ObjectRenderer* _Right)
{
	if (_Left->Object()->Pos().Y < _Right->Object()->Pos().Y)
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

///////////////////////////////////////////////////////////////

void RenderManager::Renderer_Insert(int _Key, ObjectRenderer * _ObjRenderer)
{
	std::map<int, std::list<ObjectRenderer*>>::iterator FindIter = m_Render.find(_Key);

	// Ű���� ���ٸ�
	if (FindIter == m_Render.end())
	{
		std::list<ObjectRenderer*> NewObjRender;
		NewObjRender.push_back(_ObjRenderer);
		m_Render.insert(std::map<int, std::list<ObjectRenderer*>>::value_type(_Key, NewObjRender));
		return;
	}

	FindIter->second.push_back(_ObjRenderer);

}


void RenderManager::Render()
{
	// �׸��� (Render)
	Start_MapIter = m_Render.begin();
	End_MapIter = m_Render.end();

	for (; Start_MapIter != End_MapIter; Start_MapIter++)
	{
		// Y sorting
		m_YIter = m_YSet.find(Start_MapIter->first);
		if (m_YIter != m_YSet.end())
		{
			Start_MapIter->second.sort(YSortFunc);
		}

		// �ʾȿ� �ִ� list���
		Start_ListIter = Start_MapIter->second.begin();
		End_ListIter = Start_MapIter->second.end();

		for ( ; Start_ListIter != End_ListIter; Start_ListIter++) 
		{
			if (false == (*Start_ListIter)->IsObjUpdate()) 
			{
				continue;
			}
			(*Start_ListIter)->Render();
		}
	}
}


//////////////////////////////////////////////////////YSorting

void RenderManager::YSort_On(int _idx)
{
	m_YIter = m_YSet.find(_idx);

	if (m_YIter == m_YSet.end())
	{
		m_YSet.insert(_idx);
	}
}

// ����
void RenderManager::Release()
{
	Start_MapIter = m_Render.begin();
	End_MapIter = m_Render.end();

	for (; Start_MapIter != End_MapIter; Start_MapIter++)
	{
		Start_ListIter = Start_MapIter->second.begin();
		End_ListIter = Start_MapIter->second.end();

		for (; Start_ListIter != End_ListIter;)
		{
			if (false == (*Start_ListIter)->IsObjDeath())
			{
				++Start_ListIter;
				continue;
			}

			Start_ListIter = Start_MapIter->second.erase(Start_ListIter);
		}
	}
}

