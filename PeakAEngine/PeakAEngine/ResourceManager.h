#pragma once
#include <map>

#include "Singleton.h"

#define RESOURCEMANAGER ResourceManager::GetInstance()

class RenderLayer;
class Texture2D;
class Font;
class ResourceManager final : public Singleton<ResourceManager>
{
public:
	void Init(const std::string& data);
	std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
	std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

	RenderLayer* CreateRenderLayer(int width, int height);
private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;
	std::string m_DataPath;

	std::map<std::string, std::shared_ptr<Texture2D>> m_Textures;
};
