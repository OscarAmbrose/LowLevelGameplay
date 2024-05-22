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

Player::Player()
{
	g_OnFixedUpdate.AddListener(this, std::bind(&Player::FixedUpdate, this, std::placeholders::_1));
	AddComponent<SpriteRenderer>()->setRenderLayer(1);
	AddComponent<AnimationManager>();
	rb = AddComponent<RigidBody>();
	rb->GroundedStateChanged.AddListener(this, std::bind(&Player::ChangeAnimStyle, this, std::placeholders::_1));
	rb->setGravityEnabled(true);
	AddComponent<BoxCollider>()->SetUpCollider(LLGP::Vector2f(26, 38), LLGP::Vector2f(0, 0));
	AddComponent<DebugBox>()->SetUpDebugBox();
	GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Walking")->AddAnimation("Walk", 1, 4, LLGP::Vector2i(0, 0), LLGP::Vector2i(1, 0), LLGP::Vector2i(2, 0), LLGP::Vector2i(3, 0), LLGP::Vector2i(4, 0));
	GetComponent<AnimationManager>()->GetAnimationState<AnimationState>("Walking")->AddAnimation("Reverse", 0, 1, LLGP::Vector2i(4, 0));
	GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Flying")->AddAnimation("Fall", 0, 1, LLGP::Vector2i(6, 0));
	GetComponent<AnimationManager>()->GetAnimationState<AnimationState>("Flying")->AddAnimation("Flap", 0, 1, LLGP::Vector2i(5, 0));
	GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Flying");
	AddComponent<PlayerInputController>()->getEvent<LLGP::Vector2<float>>("MoveDirection")->AddListener(this, std::bind(&Player::HandleInput, this, std::placeholders::_1));
}

Player::~Player()
{
	rb->GroundedStateChanged.RemoveListener(this, std::bind(&Player::ChangeAnimStyle, this, std::placeholders::_1));
	g_OnFixedUpdate.RemoveListener(this, std::bind(&Player::FixedUpdate, this, std::placeholders::_1));
}

void Player::HandleInput(LLGP::Vector2f value)
{
	m_InputDirection = value;
	std::cout << value.x << ", " << value.y << std::endl;
}

void Player::ChangeAnimStyle(bool isGrounded)
{
	if (isGrounded)
	{
		GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Walking");
	}
	else
	{
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
			}
			else if (m_InputDirection.x == -1)
			{
				GetComponent<SpriteRenderer>()->setFlipped(true);
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
		}
		else if (m_InputDirection.x == -1)
		{
			GetComponent<SpriteRenderer>()->setFlipped(true);
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
	
}
