#pragma once
#include <Component.h>
#include <SFML/Graphics.hpp>
#include <Vector2.h>

class PlayerController : public Component
{
public:
	PlayerController(GameObject* owner);
	~PlayerController();

	void PollInput(sf::Event event);

protected:
	//This should be equal to the controller number.
	int m_PlayerNumber = 0;

	LLGP::Vector2f m_JoystickDir;

	float m_JoystickDeadzone = 0.2f;
};
