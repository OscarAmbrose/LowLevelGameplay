#include "GradExPlayerController.h"
#include <GlobalEvents.h>

PlayerController::PlayerController(GameObject* owner) : Component(owner)
{
	g_OnPollInputs.AddListener(this, std::bind(&PlayerController::PollInput, this, std::placeholders::_1));
}

PlayerController::~PlayerController()
{
	g_OnPollInputs.RemoveListener(this, std::bind(&PlayerController::PollInput, this, std::placeholders::_1));
}

void PlayerController::PollInput(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			std::cout << "Key code: " << event.key.code << std::endl;
			switch (event.key.code)
			{

			case sf::Keyboard::A:
				std::cout << "A pressed" << std::endl;
				break;

			case sf::Keyboard::B:
				std::cout << "B pressed" << std::endl;
				break;

			default:
				std::cout << "Other key pressed" << std::endl;
				break;
			}
			break;

		case sf::Event::KeyReleased:
			switch (event.key.code)
			{

			case sf::Keyboard::A:
				std::cout << "A released" << std::endl;
				break;

			case sf::Keyboard::B:
				std::cout << "B released" << std::endl;
				break;

			default:
				//std::cout << "Other key released" << std::endl;
				break;
			}
			break;

		case sf::Event::JoystickMoved:
		{

			if (!sf::Joystick::isConnected(m_PlayerNumber)) { return; }

			float axisX = (sf::Joystick::getAxisPosition(m_PlayerNumber, sf::Joystick::X) / 100);
			float axisY = (sf::Joystick::getAxisPosition(m_PlayerNumber, sf::Joystick::Y) / 100);

			if ((axisX < m_JoystickDeadzone && axisX > -m_JoystickDeadzone))
			{
				axisX = 0;
			}
			if ((axisY < m_JoystickDeadzone && axisY > -m_JoystickDeadzone))
			{
				axisY = 0;
			}

			m_JoystickDir = LLGP::Vector2f(axisX, axisY);
			std::cout << m_JoystickDir.x << ", " << m_JoystickDir.y << std::endl;
			break;
		}

		default:
			//std::cout << "Non KeyPressed event" << std::endl;
			break;
	}

}
