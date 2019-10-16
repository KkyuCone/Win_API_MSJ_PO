#include "stdafx.h"
#include "AnimationRenderer.h"
#include "ResourceManager.h"
#include "ActorObjBase.h"
#include "GameObjectSprite.h"
#include "GameObjectMultiSprite.h"


// calss Ani ///////////////////////////////////////

AnimationRenderer::Ani::Ani(GameObjectMultiSprite* _pObjMultiSPrite, 
	size_t _AniStart, size_t _AniEnd, 
	float _AniChangeTime, bool _bLoop)
	: m_pMultiobjSprite(_pObjMultiSPrite), 
	m_AniStart(_AniStart), m_AniEnd(_AniEnd),
	m_ChangeTime(_AniChangeTime), m_bLoop(_bLoop),
	m_CurTime(0.0f), m_AniCur(0)

{
}

AnimationRenderer::Ani::~Ani()
{
}

void AnimationRenderer::Ani::Ani_Update()
{
	m_CurTime += TimeManager::Instance().DeltaTime();

	if (0 >= m_AniEnd - m_AniStart)
	{
		m_AniCur = m_AniStart;
		return;
	}

	if (m_CurTime > m_ChangeTime)
	{
		// 프레임당 건널 수 있는 수 (5월15일)
		size_t Value = (size_t)(m_CurTime / m_ChangeTime);

		if (Value >= m_AniEnd - m_AniStart)
		{
			Value %= m_AniEnd - m_AniStart;
		}

		if (false == m_bLoop)
		{
			if (m_AniCur == m_AniEnd || m_AniEnd <= m_AniCur+Value)
			{
				m_AniCur = m_AniEnd;
				return;
			}
		}

		m_AniCur -= m_AniStart;
		m_AniCur += Value;
		m_AniCur %= m_AniEnd - m_AniStart;
		m_AniCur += m_AniStart;
		m_CurTime = 0.0f;
	}
}

void AnimationRenderer::Ani::Ani_Start(size_t _Start)
{
	m_AniCur = m_AniStart + _Start;
	Tassert(m_AniCur > m_AniEnd);
}

GameObjectSprite* AnimationRenderer::Ani::Get_CurSprite()
{
	return m_pMultiobjSprite->GetSprite(m_AniCur);
}

bool AnimationRenderer::Ani::IsAniEnd()
{
	return (m_AniCur ==  m_AniEnd) && (m_CurTime >= m_ChangeTime);
}


////////////////////////////////////////////////////
AnimationRenderer::AnimationRenderer() : m_CurAnimation(nullptr)
{
}


AnimationRenderer::~AnimationRenderer()
{
	std::map<std::wstring, AnimationRenderer::Ani*>::iterator Start_Iter = m_Animations.begin();
	std::map<std::wstring, AnimationRenderer::Ani*>::iterator End_Iter = m_Animations.end();

	for (; Start_Iter != End_Iter; Start_Iter++)
	{
		delete Start_Iter->second;
	}
}

//

void AnimationRenderer::Render()
{

	if (nullptr == m_CurAnimation)
	{
		return;
	}
	
	m_CurAnimation->Ani_Update();
	GameObjectSprite* pObjSprite = m_CurAnimation->Get_CurSprite();

	if (nullptr != pObjSprite)
	{
		//F_Position RenderPos = Object()->Pos() + m_Pivot - m_Size.Half_VECTOR2();
		F_Position renderPos = RenderPos();
		if (false == pObjSprite->IsAlpha())
		{
			TransparentBlt(ResourceManager::Instance().BackBufferDC(),
				renderPos.IntX(),
				renderPos.IntY(),
				(int)(m_Size.X),
				(int)(m_Size.Y),
				pObjSprite->ObjectImageDC(),
				pObjSprite->Pos().IntX(),
				pObjSprite->Pos().IntY(),
				pObjSprite->Size().IntX(),
				pObjSprite->Size().IntY(),
				pObjSprite->TransColor()
			);
		}
		else
		{
			// 알파 적용
			F_Position renderPos = RenderPos();

			AlphaBlend(ResourceManager::Instance().BackBufferDC(),
				renderPos.IntX(),
				renderPos.IntY(),
				(int)(m_Size.X),
				(int)(m_Size.Y),
				pObjSprite->ObjectImageDC(),
				pObjSprite->Pos().IntX(),
				pObjSprite->Pos().IntY(),
				pObjSprite->Size().IntX(),
				pObjSprite->Size().IntY(),
				m_BlendFuncion);
		}
	}
}

void AnimationRenderer::Animation_Create(const wchar_t * _AniName, const wchar_t * _MultiSpriteName, 
	size_t _AniStart, size_t _AniEnd,
	bool _Loop, float _Delay)
{
	Ani* pFindAnimation = Find_Animation(_AniName);

	if (nullptr != pFindAnimation)
	{
		return;
	}

	GameObjectMultiSprite* pMultiSprite = ResourceManager::Instance().Find_MultiSprite(_MultiSpriteName);
	Tassert(nullptr == pMultiSprite);
	if (nullptr == pMultiSprite)
	{
		return;
	}

	Ani* pNewAnimation = new Ani(pMultiSprite, _AniStart, _AniEnd, _Delay, _Loop);
	pNewAnimation->Name(_AniName);
	m_Animations.insert(std::map<std::wstring, Ani*>::value_type(_AniName, pNewAnimation));

}

void AnimationRenderer::Animation_Change(const wchar_t * _AniName, size_t _idx)
{
	m_CurAnimation = Find_Animation(_AniName);
	m_CurAnimation->Ani_Start(_idx);
}

AnimationRenderer::Ani * AnimationRenderer::Find_Animation(const wchar_t * _AniName)
{
	std::map<std::wstring, Ani*>::iterator Find_Iter = m_Animations.find(_AniName);

	if (Find_Iter == m_Animations.end())
	{
		return nullptr;
	}

	return Find_Iter->second;
}


bool AnimationRenderer::IsCurAnimation(const wchar_t * _AniName)
{
	if (nullptr != m_CurAnimation)
	{
		return m_CurAnimation->NameEqual(_AniName);
	}

	return false;
}

bool AnimationRenderer::IsEndAnimation(const wchar_t * _AniName)
{
	if (false == IsCurAnimation(_AniName))
		return false;

	return IsEndAnimation();
}

bool AnimationRenderer::IsEndAnimation()
{
	if (nullptr != m_CurAnimation)
	{
		return m_CurAnimation->IsAniEnd();
	}
	return false;
}


