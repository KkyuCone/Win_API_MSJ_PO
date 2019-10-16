#pragma once
#include "ActorObjBase.h"

class SingleRenderer;
class ObjectCollision;
class SoundControl;
class GameMouseCursor : public ActorObjBase
{
private:
	SingleRenderer* m_MouseCursor;
	ObjectCollision* m_pMouseCol;
	SoundControl* m_SoundControl;
public:
	void Start_Update() override;
	void Update() override;

public:
	void MouseMove();
	void MouseState();
	void MouseClick(ObjectCollision* _This, ObjectCollision* _Other);

private:
	// Ãæµ¹
	void Collision_Stay(ObjectCollision* _This, ObjectCollision* _Other) override;


public:
	GameMouseCursor();
	~GameMouseCursor();

};

