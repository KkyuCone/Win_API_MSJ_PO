#pragma once
#include "MainSceneState.h"

class SoundControl;
class TitleStage : public MainSceneState
{
private:
	SoundControl* m_SoundControl;
private:
	void Start_Update() override;
	//void Update() override;
	void End_Debug_Update() override;
	void Loading() override;

public:
	TitleStage();
	~TitleStage();
};

