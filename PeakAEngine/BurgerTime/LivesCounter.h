#pragma once
#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/BaseObserver.h"


class Text;

class LivesCounter final : public Component, public BaseObserver
{
public:
	LivesCounter(GameObject* attachedObj, Text* pTextComponent);
	virtual ~LivesCounter() override;
	LivesCounter(const LivesCounter& other) = delete;
	LivesCounter(LivesCounter&& other) = delete;
	LivesCounter& operator=(const LivesCounter& other) = delete;
	LivesCounter& operator=(LivesCounter&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override {}

	void Notify(Component* pComponent, Event event) override;


private:
	Text* m_pText;
};

