#pragma once
#include <vector>

#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/BaseObserver.h"


class Text;

class LevelCounter final : public Component, public BaseObserver
{
public:
	LevelCounter(float size, int maxLevels, GameObject* attachedObj);
	virtual ~LevelCounter() override;
	LevelCounter(const LevelCounter& other) = delete;
	LevelCounter(LevelCounter&& other) = delete;
	LevelCounter& operator=(const LevelCounter& other) = delete;
	LevelCounter& operator=(LevelCounter&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override {}

	void Notify(Component* pComponent, Event event) override;

	void UpdateUI();

private:
	int m_MaxLevels;
	int m_Level;

	std::vector<GameObject*> m_LevelObjects;
};

