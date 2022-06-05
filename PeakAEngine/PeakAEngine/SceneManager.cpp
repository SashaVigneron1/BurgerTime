#include "PeakAEnginePCH.h"
#include "SceneManager.h"

#include "Logger.h"
#include "Scene.h"

#include "SDL.h"

void SceneManager::Update()
{
	if (m_pActiveScene)
		m_pActiveScene->Update();
}
void SceneManager::FixedUpdate()
{
	if (m_pActiveScene)
		m_pActiveScene->FixedUpdate();
}


void SceneManager::Render()
{
	if (m_pActiveScene)
		m_pActiveScene->Render();
}

void SceneManager::OnGUI()
{
	if (m_pActiveScene)
		m_pActiveScene->OnGUI();
}

void SceneManager::DestroyAllScenes()
{
	m_Scenes.clear();
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);

	if (m_Scenes.size() == 1)
		m_pActiveScene = scene.get();

	return *scene;
}

void SceneManager::LoadScene(const std::string& name)
{
	for(auto scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			m_pActiveScene = scene.get();
			return;
		}
	}

	Logger::LogError("[SceneManager] Scene with the name '" + name + "' not found.");
}

void SceneManager::LoadNextScene()
{
	bool previousSceneIsActive = false;
	for (int i{}; i < m_Scenes.size(); ++i)
	{
		if (previousSceneIsActive)
		{
			m_pActiveScene = m_Scenes[i].get();
			return;
		}

		if (m_Scenes[i].get() == m_pActiveScene)
			previousSceneIsActive = true;
	}

	Logger::LogWarning("No next scene found.");
}

void SceneManager::RemoveMarkedObjects()
{
	for(auto scene : m_Scenes)
	{
		scene->RemoveMarkedObjects();
	}
}
