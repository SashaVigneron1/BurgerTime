#include "PeakAEnginePCH.h"
#include "SceneManager.h"

#include "Renderer.h"
#include "Scene.h"

#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

#include "SDL.h"

void SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}
void SceneManager::FixedUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate();
	}
}


void SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void SceneManager::OnGUI()
{
	for (const auto& scene : m_Scenes)
	{
		scene->OnGUI();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
