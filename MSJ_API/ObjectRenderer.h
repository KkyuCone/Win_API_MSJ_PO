#pragma once
#include "ObjectSubBase.h"

class RenderManager;
class ObjectRenderer : public ObjectSubBase
{
public:
	friend ActorObjBase;			// ������Ʈ ������ ���� �� �ִ°��� ActorObjBase���� ���� ����.
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

