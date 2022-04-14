#pragma once
#include "BaseComponent.h"

class Texture2D;

class RenderComponent final : public Component
{
public:
	RenderComponent(const std::string& fileName, GameObject* attachedObj);
	virtual ~RenderComponent() override;
	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;
	void OnGUI() override {}

	void SetTexture(const std::string& fileName);
	void SetTexture(std::shared_ptr<Texture2D> newTexture) { m_pTexture = newTexture; }

private:
	std::shared_ptr<Texture2D> m_pTexture;
};

