#include "PeakAEnginePCH.h"
#include "PhysicsComponent.h"

#include <b2_body.h>
#include "b2_world.h"
#include <b2_fixture.h>
#include <b2_polygon_shape.h>

#include "RaycastCallback.h"

#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"

PhysicsComponent::PhysicsComponent(GameObject* attachedObj)
	: Component{ attachedObj }
	, m_DebugColor{1,0,0,0.3f}
{
	CreatePhysicsBody();
}

PhysicsComponent::~PhysicsComponent()
{
	if (m_pBody)
		m_pGameObject->GetScene()->GetPhysicsWorld()->DestroyBody(m_pBody);
}

void PhysicsComponent::Update()
{

}

void PhysicsComponent::FixedUpdate()
{
	auto pos = m_pGameObject->GetWorldPosition();
	m_pBody->SetTransform(b2Vec2{ pos.x, pos.y }, 0);
}

void PhysicsComponent::Render() const
{
	if (Renderer::DrawDebugPhysics)
	{
		auto pos = m_pGameObject->GetWorldPosition();
		Renderer::GetInstance().FillRect({ pos.x + m_Center.x - m_Width / 2,pos.y + m_Center.y - m_Height / 2, m_Width, m_Height }, m_DebugColor, 4);
	}
}

void PhysicsComponent::Raycast(Vector2f origin, Vector2f direction, float range, RaycastCallback* outHit)
{
	Vector2f targetP = origin + (direction * range);

	b2Vec2 bPoint1{ origin.x, origin.y };
	b2Vec2 bPoint2{ targetP.x, targetP.y };

	m_pBody->GetWorld()->RayCast(outHit, bPoint1, bPoint2);
}

void PhysicsComponent::AddBoxCollider(float width, float height, bool isTrigger, const glm::vec2& center)
{
	if (!m_pBody) CreatePhysicsBody();

	m_Center = center;
	m_Width = width;
	m_Height = height;

	b2PolygonShape boxShape{};
	boxShape.SetAsBox(width / 2, height / 2, b2Vec2{ center.x, center.y }, 0);

	b2FixtureDef fixture{};
	fixture.userData.pointer = (uintptr_t)this;
	fixture.isSensor = isTrigger;
	fixture.shape = &boxShape;

	m_pBody->CreateFixture(&fixture);
}

void PhysicsComponent::SetDebugColor(const Color4f color)
{
	m_DebugColor = color;
}

void PhysicsComponent::CreatePhysicsBody()
{
	glm::vec3 pos = m_pGameObject->GetWorldPosition();

	b2BodyDef bodyDef;
	bodyDef.userData.pointer = (uintptr_t)this;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.angle = 0.f;
	bodyDef.gravityScale = 1.0f;
	bodyDef.allowSleep = false;
	bodyDef.awake = true;
	bodyDef.fixedRotation = true;

	m_pBody = m_pGameObject->GetScene()->GetPhysicsWorld()->CreateBody(&bodyDef);
}
