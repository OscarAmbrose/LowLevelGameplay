#pragma once
#include "Player.h"
#include "SpriteRenderer.h"
#include "AnimationManager.h"
#include "Transform.h"
#include "Collider.h"
#include "Physics.h"
#include "RigidBody.h"
#include <DebugBox.h>
#include <PlayerInputController.h>
#include <GlobalEvents.h>
#include <Event.h>
#include <ScreenWrapper.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

Player::Player()
{
	g_OnFixedUpdate.AddListener(this, std::bind(&Player::FixedUpdate, this, std::placeholders::_1));
	AddComponent<SpriteRenderer>()->setRenderLayer(1);
	AddComponent<AnimationManager>();
	rb = AddComponent<RigidBody>();
	rb->GroundedStateChanged.AddListener(this, std::bind(&Player::ChangeAnimStyle, this, std::placeholders::_1));
	rb->setGravityEnabled(true);
	AddComponent<BoxCollider>()->SetUpCollider(LLGP::Vector2f(26, 38), LLGP::Vector2f(0, -3))->SetCollisionMask(0b00000011);
	GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Walking")->AddAnimation("Walk", 1, 4, LLGP::Vector2i(0, birdNumber), LLGP::Vector2i(1, birdNumber), LLGP::Vector2i(2, birdNumber), LLGP::Vector2i(3, birdNumber), LLGP::Vector2i(4, birdNumber));
	GetComponent<AnimationManager>()->GetAnimationState<AnimationState>("Walking")->AddAnimation("Reverse", 0, 1, LLGP::Vector2i(4, birdNumber));
	GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Flying")->AddAnimation("Fall", 0, 1, LLGP::Vector2i(6, birdNumber));
	GetComponent<AnimationManager>()->GetAnimationState<AnimationState>("Flying")->AddAnimation("Flap", 0, 1, LLGP::Vector2i(5, birdNumber));
	GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Flying");

	//-----------------------------------------------------------This has been removed for the general character class------------------------------------------------------------//
	AddComponent<PlayerInputController>()->getEvent<LLGP::Vector2<float>>("MoveDirection")->AddListener(this, std::bind(&Player::HandleInput, this, std::placeholders::_1));  //
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	
	AddComponent<ScreenWrapper>();
	rider = AddComponent<SpriteRenderer>()->setRenderLayer(0)->setOffSet(LLGP::Vector2f(4, -8))->setUV(LLGP::Vector2i(actualRiderColour, 3));

	this->onCollisionEnter.AddListener(this, std::bind(&Player::JoustResolution, this, std::placeholders::_1));

	SetBirdNumber(birdNumber);
	SetRiderColour('r');
}

Player::~Player()
{
	this->onCollisionEnter.RemoveListener(this, std::bind(&Player::JoustResolution, this, std::placeholders::_1));
	rb->GroundedStateChanged.RemoveListener(this, std::bind(&Player::ChangeAnimStyle, this, std::placeholders::_1));
	g_OnFixedUpdate.RemoveListener(this, std::bind(&Player::FixedUpdate, this, std::placeholders::_1));
}

void Player::HandleInput(LLGP::Vector2f value)
{
	m_InputDirection = value;
}

void Player::ChangeAnimStyle(bool isGrounded)
{
	if (isGrounded)
	{
		//std::cout << "grounded" << std::endl;
		GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Walking");
	}
	else
	{
		//std::cout << "Flying" << std::endl;
		GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Flying");
	}
}

void Player::MovePlayer(float deltaTime)
{
	LLGP::Vector2f location = transform.get()->returnPosition();
	
	LLGP::Vector2f movementForce;

	float YForce = 0;

	if (m_PreviousInputDirection.y < m_InputDirection.y && m_InputDirection.y == 1)
	{
		std::string animState = GetComponent<AnimationManager>()->ReturnActiveAnimationState();

		YForce = 200 * m_MovementSpeed;
	}

	m_PreviousInputDirection.y = m_InputDirection.y;
	
	movementForce = LLGP::Vector2f((m_InputDirection.x * m_MovementSpeed), (-YForce));

	rb->addForce(movementForce);
}

void Player::FixedUpdate(float deltaTime)
{
	MovePlayer(deltaTime);
	UpdateAnimation(deltaTime);
}

void Player::SetRiderOffsets(bool grounded)
{
	riderForward = 5;
	if (grounded)
	{
		switch (birdNumber)
		{
		case 0:
			riderHeight = 8;

			break;

		case 1:
			riderHeight = 8;

			break;

		case 2:
			riderHeight = 13;
			riderForward = 5;

			break;

		default:
			riderHeight = 8;

			break;
		}
	}
	else
	{
		switch (birdNumber)
		{
		case 0:
			riderHeight = 8;

			break;

		case 1:
			riderHeight = 8;

			break;

		case 2:
			riderHeight = 8;
			riderForward = 5;

			break;

		default:
			riderHeight = 8;

			break;
		}
	}
	
}

void Player::SetBirdNumber(int newBird)
{
	birdNumber = newBird;
	SetRiderOffsets(false);

	switch (newBird)
	{
	case 0:
		GetComponent<BoxCollider>()->SetUpCollider(LLGP::Vector2f(26, 38), LLGP::Vector2f(0, 1));
		break;
	case 1:
		GetComponent<BoxCollider>()->SetUpCollider(LLGP::Vector2f(26, 38), LLGP::Vector2f(0, 1));

		break;
	case 2:
		GetComponent<BoxCollider>()->SetUpCollider(LLGP::Vector2f(26, 38), LLGP::Vector2f(0, -3));

		break;
	default:
		GetComponent<BoxCollider>()->SetUpCollider(LLGP::Vector2f(26, 38), LLGP::Vector2f(0, 0));

		break;
	}
}

void Player::UpdateAnimation(float deltaTime)
{
	std::string animState = GetComponent<AnimationManager>()->ReturnActiveAnimationState();


#pragma region IsGrounded
	//If player is grounded do walky stuff
	if (rb->IsGrounded())
	{
		if ((m_InputDirection.x > 0 && rb->GetVelocity().x < 0) || (m_InputDirection.x < 0 && rb->GetVelocity().x > 0))
		{
			rb->setOpposingMovement(true);
		}
		else
		{
			rb->setOpposingMovement(false);
		}

		if (rb->GetOpposingMovement())
		{
			GetComponent<AnimationManager>()->GetAnimationState<AnimationState>(animState)->setActiveAnimation("Reverse");
		}
		else
		{
			GetComponent<AnimationManager>()->GetAnimationState<AnimationState>(animState)->setActiveAnimation("Walk");
		}

		if (rb->GetOpposingMovement())
		{

		}
		else
		{
			if (m_InputDirection.x == 1)
			{
				GetComponent<SpriteRenderer>()->setFlipped(false);
				rider->setFlipped(false);
			}
			else if (m_InputDirection.x == -1)
			{
				GetComponent<SpriteRenderer>()->setFlipped(true);
				rider->setFlipped(true);
			}
		}
	}

#pragma endregion 
	//If the player isnt grounded, do flappy stuff
	if (!rb->IsGrounded())
	{
		if (m_InputDirection.x == 1)
		{
			GetComponent<SpriteRenderer>()->setFlipped(false);
			rider->setOffSet(LLGP::Vector2f(riderForward, -riderHeight))->setFlipped(false);
		}
		else if (m_InputDirection.x == -1)
		{
			GetComponent<SpriteRenderer>()->setFlipped(true);
			rider->setOffSet(LLGP::Vector2f(-riderForward, -riderHeight))->setFlipped(true);
		}

		if (rb->GetVelocity().y < 0 && m_InputDirection.y == 1)
		{
			GetComponent<AnimationManager>()->GetAnimationState<AnimationState>(animState)->setActiveAnimation("Flap");
		}
		else
		{
			GetComponent<AnimationManager>()->GetAnimationState<AnimationState>(animState)->setActiveAnimation("Fall");
		}
	}
	
	SetRiderOffsets(rb->IsGrounded());

	if (rider->getFlipped())
	{
		rider->setOffSet(LLGP::Vector2f(-riderForward, -riderHeight));
	}
	else
	{
		rider->setOffSet(LLGP::Vector2f(riderForward, -riderHeight));
	}
}

void Player::JoustResolution(CollisionInfo* info)
{
	//Check whether both colliders are on the joust collision bit layer ( the second bit from the right 0b000000>X<0)
	//If they are not, return.
	if (!((CHECK_BIT(info->collider->GetCollisionMask(), 1)) && (CHECK_BIT(info->otherCollider->GetCollisionLayer(), 1))))
	{
		return;
	}


}

void Player::SetRiderColour(char newRiderColour)
{
	riderColour = newRiderColour;
	switch (riderColour)
	{
	case 'y':
		actualRiderColour = 0;
		break;
	case 'r':
		actualRiderColour = 2;
		break;
	case 'b':
		actualRiderColour = 6;
		break;
	case 'c':
		actualRiderColour = 1;
		break;
	case 'g':
		actualRiderColour = 4;
		break;
	default:
		break;
	}

	rider->setUV(LLGP::Vector2i(actualRiderColour, 3));
}
