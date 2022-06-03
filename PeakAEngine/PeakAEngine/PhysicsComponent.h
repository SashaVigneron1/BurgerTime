#pragma once

#include <functional>
#include "BaseComponent.h"
#include "structs.h"

class b2PolygonShape;
class RaycastCallback;
class b2Body;

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(GameObject* attachedObj);
	virtual ~PhysicsComponent() override;
	PhysicsComponent(const PhysicsComponent& other) = delete;
	PhysicsComponent(PhysicsComponent&& other) = delete;
	PhysicsComponent& operator=(const PhysicsComponent& other) = delete;
	PhysicsComponent& operator=(PhysicsComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override;

	void Raycast(Vector2f origin, Vector2f direction, float range, RaycastCallback* outHit);

	std::function<void(PhysicsComponent*)> OnTriggerEnter;
	std::function<void(PhysicsComponent*)> OnTriggerExit;

	void AddBoxCollider(float width, float height, bool isTrigger, const glm::vec2& center = {});
	void SetDebugColor(const Color4f color);
private:
	void CreatePhysicsBody();

	Color4f m_DebugColor;

	b2Body* m_pBody;
	glm::vec2 m_Center;
	float m_Width;
	float m_Height;

};

