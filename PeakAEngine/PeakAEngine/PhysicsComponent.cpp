#include "PeakAEnginePCH.h"
#include "PhysicsComponent.h"

#include <b2_body.h>
#include <b2_world.h>
#include <b2_fixture.h>
#include <b2_polygon_shape.h>

#include "GameObject.h"
#include "Scene.h"

PhysicsComponent::PhysicsComponent(GameObject* attachedObj)
	: Component{attachedObj}
{
	CreatePhysxBody();
}

PhysicsComponent::~PhysicsComponent()
{
	if (m_pBody)
		m_pGameObject->GetScene()->GetPhysicsWorld()->DestroyBody(m_pBody);
}

void PhysicsComponent::Update()
{
	auto pos = m_pGameObject->GetWorldPosition();
	m_pBody->SetTransform(b2Vec2{pos.x, pos.y}, 0);
}

void PhysicsComponent::FixedUpdate()
{
}

void PhysicsComponent::AddBoxCollider(float width, float height, bool isTrigger, const glm::vec2& center)
{
	if (!m_pBody) CreatePhysxBody();

	b2PolygonShape boxShape{};
	boxShape.SetAsBox(width/2, height/2, b2Vec2{ center.x, center.y }, 0);

	b2FixtureDef fixture{};
	fixture.userData.pointer = (uintptr_t)this;
	fixture.isSensor = isTrigger;
	fixture.shape = &boxShape;

	m_pBody->CreateFixture(&fixture);
}

void PhysicsComponent::CreatePhysxBody()
{
	glm::vec3 pos = m_pGameObject->GetWorldPosition();

	b2BodyDef bodyDef;
	bodyDef.userData.pointer = (uintptr_t)this;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.angle = 0.f;
	bodyDef.gravityScale = 0.0f;
	bodyDef.allowSleep = false;
	bodyDef.awake = true;
	bodyDef.fixedRotation = true;

	m_pBody = m_pGameObject->GetScene()->GetPhysicsWorld()->CreateBody(&bodyDef);
}
