#include "PeakAEnginePCH.h"
#include "Scene.h"

#include "b2_world.h"

#include "GameObject.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name)
{
	m_pb2World = new b2World(b2Vec2{ 0, 0 });
}

Scene::~Scene()
{
	for (auto& object : m_Objects)
	{
		delete object;
	}
	delete m_pb2World;
}

void Scene::Add(GameObject* object)
{
	object->SetScene(this);
	m_Objects.push_back(object);
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

