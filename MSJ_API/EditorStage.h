#pragma once
#include "MainSceneState.h"

class EditorStage : public MainSceneState
{
public:
	static float m_StartTime;
	static bool IsStart();


private:
	void Change_Scene_Start() override;

	void Start_Update() override;
	void End_Debug_Update() override;
	void Loading() override;

public:
	EditorStage();
	~EditorStage();
};

