#include "PeakAEnginePCH.h"
#include "RenderLayer.h"

RenderLayer::~RenderLayer()
{
	SDL_DestroyTexture(m_pTargetTexture);
}
