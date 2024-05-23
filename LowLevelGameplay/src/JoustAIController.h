#pragma once
#include <InputManager.h>
#include <Vector2.h>

class Character;

class JoustAIController : public InputManager
{
public:
	JoustAIController(GameObject* owner);
	~JoustAIController();

	Character* SetControlledPawn(Character* newControlledPawn);

	void Flap();

	void ChangeDirection();

	void Update(float deltaTime);

	void SetDifficultyVariables(float DirectionChangeMax, float FlapTimeMax);

protected:
	Character* m_ControlledPawn = nullptr;

	//I should put this float pattern into a struct to clean up the AI
	float m_TimeSinceLastFlap = 0.f;
	float m_MaxFlapTime = 2.f;
	float m_CurrentMaxFlapTime = 0.f;
	float m_MinFlapTime = 0.3f;

	float m_TimeSinceLastDirectionChange = 0.f;
	float m_MaxDirectionChangeTime = 10.f;
	float m_CurrentMaxDirectionChangeTime = 0.f;
	float m_MinDirectionChangeTime = 1.f;

	LLGP::Vector2f m_InputDirection;
};
