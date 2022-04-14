#pragma once

#include <functional>
#include "BaseComponent.h"

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
	void Render() const override {}

	std::function<void(PhysicsComponent*)> OnTriggerEnter;
	std::function<void(PhysicsComponent*)> OnTriggerExit;

	void AddBoxCollider(float width, float height, bool isTrigger, const glm::vec2& center = {});
private:
	void CreatePhysicsBody();

	b2Body* m_pBody;

};

