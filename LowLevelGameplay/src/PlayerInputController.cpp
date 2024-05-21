#include "PlayerInputController.h"
#include "GameObject.h"
#include "AnimationManager.h"

void PlayerInputController::DebugWASD(LLGP::Vector2<float> input)
{
	std::cout << "input: " << input.x << ", " << input.y << std::endl;
}

void PlayerInputController::PollInput(sf::Event i)
{
	//std::cout << "Polling Input" << std::endl;

	LLGP::Vector2<float> WASDInput = LLGP::Vector2<float>(0, 0);
	bool shouldJump = false;

#pragma region IF ELSE HELL
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//Skip the other inputs
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		WASDInput.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		WASDInput.x = 1;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//Skip the other inputs
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		WASDInput.y = 1;
		shouldJump = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		WASDInput.y = -1;
	}
#pragma endregion

	if (WASDInput.x != prevInput.x || WASDInput.y != prevInput.y)
	{
		invokeEvent<LLGP::Vector2<float>>("MoveDirection", WASDInput);
		prevInput = WASDInput;
	}

	if (shouldJump)
	{
		invokeEvent<int>("Jump", 1);
	}
}
