#include "stdafx.h"
#include "Util_Core.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Render_Vector.h"
#include "MainSceneState.h"
#include "RenderManager.h"
#include "ResourceManager.h"

void Util_Core::Progress()
{

	InputManager::Instance().InputManager_Update();
	TimeManager::Instance().TimeManager_Update();

	m_pCurStage->Start_Update();
	m_pCurStage->Prev_Update();
	m_pCurStage->Update();
	m_pCurStage->Late_Update();

	m_pCurStage->Obj_Render();		// 렌더

	BitBlt(m_DC, 0, 0, m_SceneSize.X, m_SceneSize.Y, ResourceManager::Instance().BackBufferDC(), 0, 0, SRCCOPY);
	
	m_pCurStage->Obj_Collision();		//충돌
	m_pCurStage->Release();
	m_pCurStage->End_Debug_Update();

	if (nullptr != m_pNextStage)
	{
		if (false == m_pNextStage->m_bLoading)
		{
			m_pNextStage->Loading();
			m_pNextStage->m_bLoading = true;
		}

		// m_pCurStage : 현재 돌고 있는 스테이지
		m_pCurStage->Change_Scene_End();		// 더 이상 이 스테이지를 돌리지 않는다.
		m_pCurStage = m_pNextStage;				// 스테이지(씬) 변경
		m_pCurStage->Change_Scene_Start();		// 스테이지 처음부분 돌리기(씬이 처음 켜질때 한번만)
		m_pNextStage = nullptr;
	}



}