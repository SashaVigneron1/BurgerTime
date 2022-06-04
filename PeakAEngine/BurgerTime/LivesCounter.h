#pragma once
#include <vector>

#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/BaseObserver.h"


class Text;

class LivesCounter final : public Component, public BaseObserver
{
public:
	LivesCounter(float size, int maxLives, GameObject* attachedObj);
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

	void SetLives(int i) { m_Lives = i; UpdateUI(); }
	void UpdateUI();

	void SetActiveSceneScoreToMine();


private:
	int m_MaxLives;
	int m_Lives;

	std::vector<GameObject*> m_LivesObjects;
};

