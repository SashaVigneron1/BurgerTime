#include "PeakAEnginePCH.h"
#include "PhysicsComponent.h"

#include <b2_body.h>
#include "b2_world.h"

#include "GameObject.h"
#include "Scene.h"

PhysicsComponent::PhysicsComponent(GameObject* attachedObj)
	: Component{attachedObj}
{
	glm::vec3 pos = m_pGameObject->GetWorldPosition();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.angle = 0.f;
	bodyDef.gravityScale = 0.0f;
	bodyDef.allowSleep = false;
	bodyDef.awake = true;
	bodyDef.fixedRotation = true;

	m_pBody = m_pGameObject->GetScene()->GetPhysicsWorld()->CreateBody(&bodyDef);
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Update()
{
}

void PhysicsComponent::FixedUpdate()
{
}
