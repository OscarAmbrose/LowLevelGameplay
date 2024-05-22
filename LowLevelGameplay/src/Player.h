#pragma once
#include <GameObject.h>
#include <Vector2.h>

class RigidBody;
class SpriteRenderer;

class Player : public GameObject
{
public:
	Player();
	~Player();

	void HandleInput(LLGP::Vector2f value);

	void ChangeAnimStyle(bool isGrounded);

	void MovePlayer(float deltaTime);

	void FixedUpdate(float deltaTime);

	void SetRiderOffsets(bool grounded);

	void SetBirdNumber(int newBird);

	void UpdateAnimation(float deltaTime);

	void JoustResolution(CollisionInfo* info);

	void SetRiderColour(char newRiderColour);


protected:
	LLGP::Vector2f m_InputDirection;
	LLGP::Vector2f m_PreviousInputDirection;
	RigidBody* rb;
	float m_MovementSpeed = 300.f;
	SpriteRenderer* rider;
	int birdNumber = 2;
	int riderHeight = 8;
	int riderForward = 5;
	char riderColour = 'y';
	int actualRiderColour = 0;
};
