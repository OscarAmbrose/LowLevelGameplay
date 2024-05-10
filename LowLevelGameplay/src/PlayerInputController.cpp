#include "PlayerInputController.h"

void PlayerInputController::PollInput(sf::Event i)
{
	//std::cout << "Polling Input" << std::endl;

	Vector2<float> WASDInput = Vector2<float>(0, 0);
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
		invokeEvent<Vector2<float>>("MoveDirection", WASDInput);
		prevInput = WASDInput;
	}

	if (shouldJump)
	{
		invokeEvent<int>("Jump", 1);
	}
}
