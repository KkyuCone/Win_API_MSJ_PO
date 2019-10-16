#pragma once
#include "ActorObjBase.h"

class TitleBackground : public ActorObjBase
{
public:
	void Start_Update() override;
	void Update() override;
	void Late_Update() override;

public:
	TitleBackground();
	~TitleBackground();
};

