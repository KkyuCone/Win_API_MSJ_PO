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

	m_pCurStage->Obj_Render();		// ����

	BitBlt(m_DC, 0, 0, m_SceneSize.X, m_SceneSize.Y, ResourceManager::Instance().BackBufferDC(), 0, 0, SRCCOPY);
	
	m_pCurStage->Obj_Collision();		//�浹
	m_pCurStage->Release();
	m_pCurStage->End_Debug_Update();

	if (nullptr != m_pNextStage)
	{
		if (false == m_pNextStage->m_bLoading)
		{
			m_pNextStage->Loading();
			m_pNextStage->m_bLoading = true;
		}

		// m_pCurStage : ���� ���� �ִ� ��������
		m_pCurStage->Change_Scene_End();		// �� �̻� �� ���������� ������ �ʴ´�.
		m_pCurStage = m_pNextStage;				// ��������(��) ����
		m_pCurStage->Change_Scene_Start();		// �������� ó���κ� ������(���� ó�� ������ �ѹ���)
		m_pNextStage = nullptr;
	}



}