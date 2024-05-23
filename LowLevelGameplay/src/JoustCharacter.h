#pragma once
#include <GameObject.h>
#include <Vector2.h>

class RigidBody;
class SpriteRenderer;

class Character : public GameObject
{
public:
	Character();
	~Character();

	void initialiseCharacter(int charBirdNumber, char charRiderCharacter, uint8_t collisionMask, uint8_t collisionLayer);

	void HandleInput(LLGP::Vector2f value);

	void ChangeAnimStyle(bool isGrounded);

	void MovePlayer(float deltaTime);

	void FixedUpdate(float deltaTime);

	void SetRiderOffsets(bool grounded);

	void SetBirdNumber(int newBird);

	void UpdateAnimation(float deltaTime);

	void JoustResolution(CollisionInfo* info);

	void SetRiderColour(char newRiderColour);

	static std::shared_ptr<Character> CreateAICharacter(char characterColour, LLGP::Vector2f location);

protected:
	LLGP::Vector2f m_InputDirection;
	LLGP::Vector2f m_PreviousInputDirection;
	RigidBody* m_Rb;
	float m_MovementSpeed = 300.f;
	SpriteRenderer* m_Rider;
	int m_BirdNumber = 2;
	int m_RiderHeight = 8;
	int m_RiderForward = 5;
	char m_RiderColour = 'y';
	int m_ActualRiderColour = 0;
	bool m_CharIsAlive = false;
};
