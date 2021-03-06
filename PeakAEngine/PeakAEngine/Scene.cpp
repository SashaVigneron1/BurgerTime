#include "PeakAEnginePCH.h"
#include "Scene.h"

#include <b2_world.h>

#include "GameObject.h"
#include "imgui.h"
#include "Renderer.h"
#include "Time.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name{name}
	, m_pPhysicsHandler{ new PhysicsHandler() }
	, m_EnableOnGUI{false}
{
}

Scene::~Scene()
{
	m_pPhysicsHandler->StopContactListener();
	for (auto& object : m_Objects)
	{
		delete object;
	}
	delete m_pPhysicsHandler;
}

GameObject* Scene::Add(GameObject* object)
{
	m_Objects.push_back(object);
	return object;
}

void Scene::Remove(GameObject* object)
{
	m_ObjectsToDestroy.push_back(object);
}

void Scene::RemoveMarkedObjects()
{
	// Destroy Objects
	for (int i{}; i < (int)m_ObjectsToDestroy.size(); ++i)
	{
		for (int j{}; j < (int)m_Objects.size(); ++j)
		{
			if (m_Objects[j] == m_ObjectsToDestroy[i])
			{
				delete m_Objects[j];
				m_Objects[j] = m_Objects.back();
				m_Objects.pop_back();
			}
		}
	}
	m_ObjectsToDestroy.clear();
}

void Scene::Update()
{
	for (int i{}; i < (int)m_Objects.size(); ++i)
		if (!m_Objects[i]->GetParent()) m_Objects[i]->Update();
}
void Scene::FixedUpdate()
{
	if (auto physicsWorld = GetPhysicsWorld())
	{
		physicsWorld->Step(Time::FixedTime(), 1, 10);
		physicsWorld->ClearForces();
	}

	for (auto& object : m_Objects)
	{
		if (!object->GetParent()) object->FixedUpdate();
	}
}


void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::OnGUI()
{
	if (!m_EnableOnGUI) return;


	ImGui::Begin(m_Name.c_str());
	ImGui::Checkbox("Enable Debugging", &Renderer::DrawDebugPhysics);
	for (const auto& object : m_Objects)
	{
		object->OnGUI();
	}
	ImGui::End();
}

