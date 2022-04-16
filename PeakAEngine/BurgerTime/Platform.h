#pragma once
#include "PeakAEngine/BaseComponent.h"


enum class PlatformType
{
	normal,
	coupled
};

class Platform final : public Component
{
public:
	Platform(GameObject* pGameObject);
	virtual ~Platform() override;
	Platform(const Platform& other) = delete;
	Platform(Platform&& other) noexcept = delete;
	Platform& operator=(const Platform& other) = delete;
	Platform& operator=(Platform&& other) noexcept = delete;

	void Update() override {}
	void FixedUpdate() override {}
	void OnGUI() override {}
	void Render() const override {}

private:
};
