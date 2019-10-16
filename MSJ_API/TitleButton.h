#pragma once
#include "ActorObjBase.h"

class SingleRenderer;
class AnimationRenderer;
class TitleButton : public ActorObjBase
{
private:
	SingleRenderer* m_pTitleButton_1P;
	SingleRenderer* m_pTitleButton_2P;
	SingleRenderer* m_pTitleButton_Editor;
	SingleRenderer* m_pTitleButton_Exit;

private:
	AnimationRenderer* m_FadeInRenderer;
	bool m_FadeIn;

public:
	void Start_Update() override;
	void Prev_Update() override;
	void Update() override;
	void Late_Update() override;


public:
	void InputMouseButton();


public:
	TitleButton();
	~TitleButton();
};

