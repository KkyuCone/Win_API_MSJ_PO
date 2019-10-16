#include "stdafx.h"
#include "EditorExit.h"
#include "Util_Core.h"


EditorExit::EditorExit()
{
}


EditorExit::~EditorExit()
{
}

void EditorExit::Start_Update()
{

}

void EditorExit::Update()
{
	if (true == InputManager::Instance().DownStay(L"KEY_F5"))
	{
		Util_Core::Instance().ChangeStage(ALLSTAGE::TITLE);
	}
}

