#pragma once
#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/BaseObserver.h"


class Text;

class ScoreCounter final : public Component, public BaseObserver
{
public:
	ScoreCounter(GameObject* attachedObj, Text* pTextComponent);
	virtual ~ScoreCounter() override;
	ScoreCounter(const ScoreCounter& other) = delete;
	ScoreCounter(ScoreCounter&& other) = delete;
	ScoreCounter& operator=(const ScoreCounter& other) = delete;
	ScoreCounter& operator=(ScoreCounter&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override {}

	void Notify(Component* pComponent, Event event) override;

	void UpdateText();
	int GetScore() const { return m_Score; }
	void SetScore(int i) { m_Score = i; UpdateText(); }

	void SetActiveSceneScoreToMine();

private:
	Text* m_pText;
	int m_Score;
};
