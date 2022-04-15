#include "PeakAEnginePCH.h"
#include "Scene.h"

#include <b2_world.h>

#include "GameObject.h"
#include "Time.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name)
{
	m_pPhysicsHandler = new PhysicsHandler();
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

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		if (!object->GetParent()) object->Update();
	}
}
void Scene::FixedUpdate()
{
	if (auto physicsWorld = GetPhysicsWorld())
	{
		physicsWorld->Step(Time::FixedTime(), 10, 8);
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
	for (const auto& object : m_Objects)
	{
		object->OnGUI();
	}
}

