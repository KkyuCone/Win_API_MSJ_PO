#include "stdafx.h"
#include "SelectBackgorund2P.h"
#include "ResourceManager.h"
#include "SingleRenderer.h"
#include "GameObjectImage.h"

///////////////////////////////////////////////
SelectBackgorund2P::SelectBackgorund2P()
{
}


SelectBackgorund2P::~SelectBackgorund2P()
{
}

//////////////////////////////////////////////

void SelectBackgorund2P::Start_Update()
{
	SingleRenderer* m_SelectSceneRenderer = Create_Renderer<SingleRenderer>(0);
	m_SelectSceneRenderer->SettingSprite(L"SelectBackground_2P.bmp");
	m_SelectSceneRenderer->Size(F_Position{ 1024, 768 });
	m_SelectSceneRenderer->Pivot(F_Position{ 1024 / 2, 768 / 2 });
}

