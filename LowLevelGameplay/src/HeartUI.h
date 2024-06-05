#pragma once
#include <GameObject.h>
#include <Vector2.h>

class SpriteRenderer;

class HeartUI : public GameObject
{
public:
	HeartUI();
	~HeartUI();

	HeartUI* SetMaxLives(int newLives, bool isFilling);
	HeartUI* SetMaxLives(int newLives);
	inline int GetMaxLives() { return MaxLives; }

	void SetHeartOffsets();

private:
	int MaxLives = 3;
	int CurrentLives = 3;
	
	LLGP::Vector2i fullHeartLocation = LLGP::Vector2i(0, 12);

	float StepDistance = 0.f;

	float TotalSize = 0.f;

	int PlayerNumber = -1;

	std::vector<SpriteRenderer*> renderers;
};
