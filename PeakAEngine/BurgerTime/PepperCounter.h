#pragma once
#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/BaseObserver.h"


class Text;

class PepperCounter final : public Component, public BaseObserver
{
public:
	PepperCounter(GameObject* attachedObj, Text* pTextComponent);
	virtual ~PepperCounter() override;
	PepperCounter(const PepperCounter& other) = delete;
	PepperCounter(PepperCounter&& other) = delete;
	PepperCounter& operator=(const PepperCounter& other) = delete;
	PepperCounter& operator=(PepperCounter&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override {}

	void Notify(Component* pComponent, Event event) override;

	void UpdateText();

	int GetPepperCount() const { return m_PepperCount; }

private:
	Text* m_pText;
	int m_PepperCount;
};
