#pragma once
#include "BaseComponent.h"

class Transform final : public Component
{
public:
	Transform(const glm::vec3 position, GameObject* attachedObj);
	virtual ~Transform() override;
	Transform(const Transform& other) = delete;
	Transform(Transform&& other) = delete;
	Transform& operator=(const Transform& other) = delete;
	Transform& operator=(Transform&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override {}

	void Translate(float x, float y, float z) { m_LocalPosition += glm::vec3{ x,y,z };}
	void SetWorldPosition(float x, float y, float z);
	void SetWorldPosition(const glm::vec3& pos) { m_WorldPosition = pos; }
	void SetLocalPosition(float x, float y, float z);
	void SetLocalPosition(const glm::vec3& pos) { m_LocalPosition = pos; }
	const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
	const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
private:
	glm::vec3 m_WorldPosition;
	glm::vec3 m_LocalPosition;
};

