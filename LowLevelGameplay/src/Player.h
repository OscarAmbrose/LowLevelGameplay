#pragma once
#include <GameObject.h>
#include <Vector2.h>

class RigidBody;

class Player : public GameObject
{
public:
	Player();
	~Player();

	void HandleInput(LLGP::Vector2f value);

	void ChangeAnimStyle(bool isGrounded);

	void MovePlayer(float deltaTime);

	void FixedUpdate(float deltaTime);

	void UpdateAnimation(float deltaTime);
protected:
	LLGP::Vector2f m_InputDirection;
	LLGP::Vector2f m_PreviousInputDirection;
	RigidBody* rb;
	float m_MovementSpeed = 300.f;
};
