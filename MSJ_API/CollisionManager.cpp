#include "stdafx.h"
#include "CollisionManager.h"
#include "ObjectCollision.h"

////// CollisionCroup 클래스

CollisionManager::CollisionCroup::CollisionCroup()
{

}
CollisionManager::CollisionCroup::~CollisionCroup()
{

}


void CollisionManager::CollisionCroup::Link(CollisionCroup* _OtherGroup)
{
	m_OtherStart = m_OtherColGroup.begin();
	m_OtherEnd = m_OtherColGroup.end();

	for ( ; m_OtherStart != m_OtherEnd; ++m_OtherStart)
	{
		// 같은거 있으면 안되니까 return
		if (*m_OtherStart == _OtherGroup)
		{
			return;
		}
	}

	Tassert(nullptr == _OtherGroup);

	if (nullptr == _OtherGroup)
	{
		return;
	}

	m_OtherColGroup.push_back(_OtherGroup);
}


void CollisionManager::CollisionCroup::Insert_Collision(ObjectCollision* _ObjCol)
{
	m_ObjColList.push_back(_ObjCol);
}


void CollisionManager::CollisionCroup::Collision_Check(CollisionCroup* _OtherGroup)
{
	// 나 = 나(_OtherGroup) 일 경우 (같은 그룹의 경우) 
	if (this == _OtherGroup)
	{
		// 다른 그룹의 경우 
		m_ThisStartIter = m_ObjColList.begin();		// 내 그룹
		m_ThisEndIter = m_ObjColList.end();

		for (; m_ThisStartIter != m_ThisEndIter; ++m_ThisStartIter)
		{
			if (false == (*m_ThisStartIter)->IsObjUpdate())
			{
				continue;
			}

			m_OtherStartIter = m_ThisStartIter;  // 다른그룹
			m_OtherEndIter = m_ThisEndIter;

			++m_OtherStartIter;

			for (; m_OtherStartIter != m_OtherEndIter; ++m_OtherStartIter)
			{
				if (false == (*m_OtherStartIter)->IsObjUpdate())
				{
					continue;
				}

				(*m_ThisStartIter)->Collision_Check(*m_OtherStartIter);
			}

		}
	}
	else
	{
		// 다른 그룹의 경우 
		m_ThisStartIter = m_ObjColList.begin();		// 내 그룹
		m_ThisEndIter = m_ObjColList.end();

		for (; m_ThisStartIter != m_ThisEndIter; ++m_ThisStartIter)
		{
			if (false == (*m_ThisStartIter)->IsObjUpdate())
			{
				continue;
			}

			m_OtherStartIter = _OtherGroup->m_ObjColList.begin();   // 다른그룹
			m_OtherEndIter = _OtherGroup->m_ObjColList.end();

			for (; m_OtherStartIter != m_OtherEndIter; ++m_OtherStartIter)
			{
				if (false == (*m_OtherStartIter)->IsObjUpdate())
				{
					continue;
				}

				(*m_ThisStartIter)->Collision_Check(*m_OtherStartIter);
			}

		}
	}
}

void CollisionManager::CollisionCroup::Collision_Update()
{
	m_OtherStart = m_OtherColGroup.begin();
	m_OtherEnd = m_OtherColGroup.end();

	for ( ; m_OtherStart != m_OtherEnd; ++m_OtherStart)
	{
		CollisionCroup* OtherColList = *m_OtherStart;
		Collision_Check(OtherColList);
	}
}

void CollisionManager::CollisionCroup::Collision_Setting()
{
	m_ThisStartIter = m_ObjColList.begin();
	m_ThisEndIter = m_ObjColList.end();

	for (; m_ThisStartIter != m_ThisEndIter; ++m_ThisStartIter)
	{
		(*m_ThisStartIter)->ParentPosSetting();
	}
}

//삭제
void CollisionManager::CollisionCroup::Release()
{
	m_ThisStartIter = m_ObjColList.begin();
	m_ThisEndIter = m_ObjColList.end();

	for ( ; m_ThisStartIter != m_ThisEndIter; )
	{
		if (true == (*m_ThisStartIter)->IsObjDeath())
		{
			m_ThisStartIter = m_ObjColList.erase(m_ThisStartIter);
		}
		else
		{
			++m_ThisStartIter;
		}
	}
}

// 디버그
void CollisionManager::CollisionCroup::DebugRender()
{
	m_ThisStartIter = m_ObjColList.begin();
	m_ThisEndIter = m_ObjColList.end();

	for ( ; m_ThisStartIter != m_ThisEndIter; ++m_ThisStartIter)
	{
		(*m_ThisStartIter)->DebugRender();
	}
}



////// CollisionManager 클래스

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
	std::map<std::wstring, CollisionCroup*>::iterator Start = m_ColGroupMap.begin();
	std::map<std::wstring, CollisionCroup*>::iterator End = m_ColGroupMap.end();

	for ( ; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			delete Start->second;
		}
	}

	m_ColGroupMap.clear();
}

CollisionManager::CollisionCroup* CollisionManager::FindColGroup(const wchar_t* _GroupName)
{
	m_FindGroupIter = m_ColGroupMap.find(_GroupName);

	// 해당 그룹이 없다면 추가
	if (m_FindGroupIter == m_ColGroupMap.end())
	{
		CollisionCroup* pColGroup = new CollisionCroup;
		pColGroup->Name = _GroupName;
		m_ColGroupMap.insert(std::map<std::wstring, CollisionCroup*>::value_type(_GroupName, pColGroup));
		return pColGroup;
	}

	return m_FindGroupIter->second;
}

void CollisionManager::Insert_Collision(const wchar_t* _GroupName, ObjectCollision* _ObjCol)
{
	CollisionCroup* pColGroup = FindColGroup(_GroupName);		// 그룹찾기

	// 해당 그룹이 없다면 ( 그룹이 생성되지 않았다면 )
	Tassert(nullptr == pColGroup);
	if (nullptr == pColGroup)
	{
		return;
	}

	pColGroup->Insert_Collision(_ObjCol);

}

void CollisionManager::Link(const wchar_t* _Left, const wchar_t* _Right)
{
	CollisionCroup* pLeft = FindColGroup(_Left);
	CollisionCroup* pRight = FindColGroup(_Right);

	Tassert(nullptr == pLeft);
	Tassert(nullptr == pRight);

	if (nullptr == pLeft || nullptr == pRight)
	{
		return;
	}

	// 중복해서 할필요가 없음  pRight->Link(pLeft)
	pLeft->Link(pRight);
}


// 모든 그룹의 Collision 체크를 여기서 하므로 모든 스테이지(Scene)에선 이걸 실행해줘야한다.
void CollisionManager::Collision_Update()
{
	std::map<std::wstring, CollisionCroup*>::iterator Start_Iter = m_ColGroupMap.begin();
	std::map<std::wstring, CollisionCroup*>::iterator End_Iter = m_ColGroupMap.end();

	for ( ; Start_Iter != End_Iter; ++Start_Iter)
	{
		if (nullptr != Start_Iter->second)
		{
			Start_Iter->second->Collision_Setting();
			Start_Iter->second->Collision_Update();
		}
	}
}

void CollisionManager::Release()
{
	std::map<std::wstring, CollisionCroup*>::iterator Start_Iter = m_ColGroupMap.begin();
	std::map<std::wstring, CollisionCroup*>::iterator End_Iter = m_ColGroupMap.end();

	for (; Start_Iter != End_Iter; ++Start_Iter)
	{
		if (nullptr != Start_Iter->second)
		{
			Start_Iter->second->Release();
		}
	}
}

// 디버그 
void CollisionManager::DebugRender()
{
	std::map<std::wstring, CollisionCroup*>::iterator Start_Iter = m_ColGroupMap.begin();
	std::map<std::wstring, CollisionCroup*>::iterator End_Iter = m_ColGroupMap.end();

	for ( ; Start_Iter != End_Iter; ++Start_Iter)
	{
		if (nullptr != Start_Iter->second)
		{
			Start_Iter->second->DebugRender();
		}
	}
}
