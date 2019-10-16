#include "stdafx.h"
#include "SingleRenderer.h"
#include "ResourceManager.h"
#include "ActorObjBase.h"
#include "GameObjectSprite.h"

// 이 라이브러리를 추가해줘야 사용이 가능
#pragma comment(lib, "msimg32.lib")

////////////////////////////////////////////

SingleRenderer::SingleRenderer() : m_pSpriteImage(nullptr)
{
}


SingleRenderer::~SingleRenderer()
{
}

//////////////////////////////////////////////

void SingleRenderer::SettingSprite(const wchar_t * _pImageName)
{
	//m_pSpriteImage = ResourceManager::Instance().Find_Image(_pImageName);
	m_pSpriteImage = ResourceManager::Instance().Find_Sprite(_pImageName);
}

void SingleRenderer::SettingSprite(const wchar_t * _pImageName, size_t _Count)
{
	m_pSpriteImage = ResourceManager::Instance().Find_Sprite(_pImageName, _Count);
}

void SingleRenderer::Render()
{
	if (nullptr != m_pSpriteImage)
	{
		// F_Position RenderPos = Object()->Pos() + m_Pivot - m_Size.Half_VECTOR2();

		F_Position Render_Pos = RenderPos();

		if (false == m_pSpriteImage->IsAlpha())
		{
			TransparentBlt(ResourceManager::Instance().BackBufferDC(),
				Render_Pos.IntX(),
				Render_Pos.IntY(),
				(int)(m_Size.X),
				(int)(m_Size.Y),
				m_pSpriteImage->ObjectImageDC(),
				m_pSpriteImage->Pos().IntX(),
				m_pSpriteImage->Pos().IntY(),
				m_pSpriteImage->Size().IntX(),
				m_pSpriteImage->Size().IntY(),
				m_pSpriteImage->TransColor()
			);
		}
		else
		{

			AlphaBlend(ResourceManager::Instance().BackBufferDC(),
				Render_Pos.IntX(),
				Render_Pos.IntY(),
				(int)(m_Size.X),
				(int)(m_Size.Y),
				m_pSpriteImage->ObjectImageDC(),
				m_pSpriteImage->Pos().IntX(),
				m_pSpriteImage->Pos().IntY(),
				m_pSpriteImage->Size().IntX(),
				m_pSpriteImage->Size().IntY(),
				m_BlendFuncion);

		}

	
	}
}