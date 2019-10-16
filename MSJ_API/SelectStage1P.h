#pragma once
#include "MainSceneState.h"

class SoundControl;
class SelectStage1P : public MainSceneState
{
public:
	SelectStage1P();
	~SelectStage1P();

public:
	void Start_Update() override;
	void End_Debug_Update() override;
	void Loading() override;
};

