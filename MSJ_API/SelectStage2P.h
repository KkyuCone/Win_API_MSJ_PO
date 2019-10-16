#pragma once
#include "MainSceneState.h"

class SelectStage2P : public MainSceneState
{
private:
	void Start_Update() override;
	void End_Debug_Update() override;
	void Loading() override;

public:
	SelectStage2P();
	~SelectStage2P();
};

