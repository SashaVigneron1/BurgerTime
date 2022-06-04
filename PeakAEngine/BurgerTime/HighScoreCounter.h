#pragma once
#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/BaseObserver.h"
#include "PeakAEngine/FileIO.h"


class Text;

class HighScoreCounter final : public Component, public BaseObserver
{
public:
	HighScoreCounter(GameObject* attachedObj, Text* pTextComponent);
	virtual ~HighScoreCounter() override;
	HighScoreCounter(const HighScoreCounter& other) = delete;
	HighScoreCounter(HighScoreCounter&& other) = delete;
	HighScoreCounter& operator=(const HighScoreCounter& other) = delete;
	HighScoreCounter& operator=(HighScoreCounter&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override {}

	void Notify(Component* pComponent, Event event) override;

	void UpdateText();

private:
	FileIO m_fileIO;
	Text* m_pText;
	int m_Score;
};
