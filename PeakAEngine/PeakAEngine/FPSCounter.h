#pragma once
#include "BaseComponent.h"

class Font;
class Text;

class FPSCounter final : public Component
{
public:
	FPSCounter(GameObject* attachedObj, Text* pTextComponent);
	virtual ~FPSCounter() override;
	FPSCounter(const FPSCounter& other) = delete;
	FPSCounter(FPSCounter&& other) = delete;
	FPSCounter& operator=(const FPSCounter& other) = delete;
	FPSCounter& operator=(FPSCounter&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override {}

private:
	Text* m_pText;
	std::vector<float> m_FrameTimes;
	int m_CurrIndex;
	int m_NrOfTimes;
};

