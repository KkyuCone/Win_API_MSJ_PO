#pragma once
#include "ActorObjBase.h"

class ObjectCollision;
class EditorExit : public ActorObjBase
{

private:
	ObjectCollision* m_pColEditorExit;

public:
	void Start_Update() override;
	void Update() override;

public:
	EditorExit();
	~EditorExit();
};

