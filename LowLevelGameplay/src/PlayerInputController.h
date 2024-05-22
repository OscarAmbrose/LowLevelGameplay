#pragma once
#include "InputManager.h"
#include "Vector2.h"

class RigidBody;

class PlayerInputController : public InputManager
{
public:
	PlayerInputController(GameObject* owner);

	~PlayerInputController();

	void DebugWASD(LLGP::Vector2<float> input);

	void DebugJump(int jumpInt)
	{
		//std::cout << "Player shoud Jump" << std::endl;
	}

	void PollInput(sf::Event i);

private:
	LLGP::Vector2<float> prevInput = LLGP::Vector2<float>(0, 0);
	RigidBody* player = nullptr;
};
