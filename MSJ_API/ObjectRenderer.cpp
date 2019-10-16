#include "stdafx.h"
#include "ObjectRenderer.h"
#include "ActorObjBase.h"


//////////////////////////////////////////////////

ObjectRenderer::ObjectRenderer() : m_bCamera(true)
{
	m_BlendFuncion.BlendOp = AC_SRC_OVER;
	m_BlendFuncion.BlendFlags = 0;
	m_BlendFuncion.AlphaFormat = AC_SRC_ALPHA;
	m_BlendFuncion.SourceConstantAlpha = 255;
}


ObjectRenderer::~ObjectRenderer()
{
}

/////////////////////////////////////////////////

F_Position ObjectRenderer::RenderPos()
{
	F_Position RenderPos = Object()->Pos() + (m_Pivot * Object()->ScaleRatio()) - m_Size.Half_VECTOR2();

	// 카메라 이동값을 뺌 여부
	if (true == m_bCamera)
	{
		RenderPos -= Object()->Stage()->CameraPos();
	}
	return RenderPos;
}
