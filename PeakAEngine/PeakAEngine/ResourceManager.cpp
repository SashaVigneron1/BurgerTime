#include "PeakAEnginePCH.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "RenderLayer.h"

void ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(RENDERER.GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + file, size);
}

RenderLayer* ResourceManager::CreateRenderLayer(int width, int height)
{
	auto target = SDL_CreateTexture(RENDERER.GetSDLRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetTextureBlendMode(target, SDL_BLENDMODE_BLEND);
	return new RenderLayer(target);
}
