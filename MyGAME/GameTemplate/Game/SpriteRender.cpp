#include "stdafx.h"
#include "SpriteRender.h"
#include "FixedUI.h"

void SpriteRender::Init(const char* name, int width, int height)
{
	SpriteInitData spdata;
	spdata.m_ddsFilePath[0] = name;
	spdata.m_fxFilePath = "Assets/shader/sprite.fx";

	spdata.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	spdata.m_width = width;
	spdata.m_height = height;

	m_sprite.Init(spdata);
}
