#pragma once
#include "ObjectSubBase.h"

class RenderManager;
class ObjectRenderer : public ObjectSubBase
{
public:
	friend ActorObjBase;			// 오브젝트 본인을 지울 수 있는것은 ActorObjBase에서 지울 것임.
	friend RenderManager;

protected:

	bool m_bCamera;
	BLENDFUNCTION m_BlendFuncion;

public:
	void CameraMode(bool _Value)
	{
		m_bCamera = _Value;
	}

	void Set_Alpha(BYTE _Alpha)
	{
		m_BlendFuncion.SourceConstantAlpha = _Alpha;
	}

	BYTE Get_Alpha()
	{
		return m_BlendFuncion.SourceConstantAlpha;
	}

public:
	F_Position RenderPos();

private:
	virtual void Render() = 0;

protected:
	ObjectRenderer();
	~ObjectRenderer();
};

