#include <JoustAIController.h>
#include <Vector2.h>
#include "JoustPlayerCharacter.h"
#include <GameObject.h>

JoustAIController::JoustAIController(GameObject* owner) : InputManager(owner)
{
	m_InputDirection = LLGP::Vector2f(1, 0);
	//Create event.
	addEvent<InputAsset<LLGP::Vector2<float>>>("MoveDirection");
	//Get your owner (must be casted to character).
	SetControlledPawn(static_cast<Character*>(owner));
	//Bind the character's handle input to our move event.
	getEvent<LLGP::Vector2<float>>("MoveDirection")->AddListener(m_ControlledPawn, std::bind(&Character::HandleInput, m_ControlledPawn, std::placeholders::_1));
}

JoustAIController::~JoustAIController()
{
	getEvent<LLGP::Vector2<float>>("MoveDirection")->RemoveListener(m_ControlledPawn, std::bind(&Character::HandleInput, m_ControlledPawn, std::placeholders::_1));
}

Character* JoustAIController::SetControlledPawn(Character* newControlledPawn)
{
	m_ControlledPawn = newControlledPawn;
	return m_ControlledPawn;
}

void JoustAIController::Flap()
{
	m_InputDirection.y = 1;
}

void JoustAIController::ChangeDirection()
{
	m_InputDirection.x *= -1;
}

void JoustAIController::Update(float deltaTime)
{
	if (!_GameObject->GetActive())
	{
		return;
	}
	Component::Update(deltaTime);
	//Dont do anything until you're initialised
	if (!Started)
	{
		return;
	}

	m_TimeSinceLastFlap += deltaTime;

	// If you have passed the minimum flap time, stop yo' flappin
	if (m_TimeSinceLastFlap > 0.2f)
	{
		m_InputDirection.y = 0;
	}

	// Flap if you haven't flapped in a while.
	if (m_TimeSinceLastFlap >= m_CurrentMaxFlapTime)
	{
		//m_InputDirection.x *= -1;
		Flap();
		m_TimeSinceLastFlap -= m_CurrentMaxFlapTime;
		m_CurrentMaxFlapTime = m_MinFlapTime + (static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (m_MaxFlapTime - m_MinFlapTime))));
	}

	m_TimeSinceLastDirectionChange += deltaTime;

	if (m_TimeSinceLastDirectionChange > m_CurrentMaxDirectionChangeTime)
	{
		ChangeDirection();
		m_TimeSinceLastDirectionChange -= m_CurrentMaxDirectionChangeTime;
		m_CurrentMaxDirectionChangeTime = m_MinDirectionChangeTime + (static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (m_MaxDirectionChangeTime - m_MinDirectionChangeTime))));
	}

	invokeEvent<LLGP::Vector2<float>>("MoveDirection", m_InputDirection);
}

void JoustAIController::SetDifficultyVariables(float DirectionChangeMax, float FlapTimeMax)
{
	m_MaxDirectionChangeTime = DirectionChangeMax;
	m_MaxFlapTime = FlapTimeMax;
}
