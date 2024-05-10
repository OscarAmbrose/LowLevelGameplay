#pragma once
#include "InputManager.h"

class PlayerInputController : public InputManager
{
public:
	PlayerInputController(GameObject* owner) : InputManager(owner)
	{
		addEvent<InputAsset<Vector2<float>>>("MoveDirection")->getEvent<Vector2<float>>()->AddListener(this, std::bind(&PlayerInputController::DebugWASD, this, std::placeholders::_1));
		addEvent<InputAsset<int>>("Jump")->getEvent<int>()->AddListener(this, std::bind(&PlayerInputController::DebugJump, this, std::placeholders::_1));
	}

	~PlayerInputController(){}

	void DebugWASD(Vector2<float> input)
	{
		std::cout << "input: " << input.x << ", " << input.y << std::endl;
	}

	void DebugJump(int jumpInt)
	{
		std::cout << "Player shoud Jump" << std::endl;
	}

	void PollInput(sf::Event i);

private:
	Vector2<float> prevInput = Vector2<float>(0, 0);
};
