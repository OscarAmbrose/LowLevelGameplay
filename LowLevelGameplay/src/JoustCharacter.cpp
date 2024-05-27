#pragma once
#include "JoustCharacter.h"
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
#include <JoustAIController.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

Character::Character()
{
	//initialiseCharacter(1, 'r', 0b00000111, 0b00000100);
}

Character::~Character()
{
	this->onCollisionEnter.RemoveListener(this, std::bind(&Character::JoustResolution, this, std::placeholders::_1));
	m_Rb->GroundedStateChanged.RemoveListener(this, std::bind(&Character::ChangeAnimStyle, this, std::placeholders::_1));
	g_OnFixedUpdate.RemoveListener(this, std::bind(&Character::FixedUpdate, this, std::placeholders::_1));
}

void Character::initialiseCharacter(int charBirdNumber, char charRiderColour, uint8_t collisionMask, uint8_t collisionLayer)
{
	//Add sprite renderers and set up their informations
	AddComponent<SpriteRenderer>()->setRenderLayer(1);
	m_Rider = AddComponent<SpriteRenderer>()->setRenderLayer(0)->setOffSet(LLGP::Vector2f(4, -8))->setUV(LLGP::Vector2i(m_ActualRiderColour, 3));

	//Add Animation Manager
	AddComponent<AnimationManager>();

	//Add RigidBody (needed for certain animation states in the animation manager, such as walking.) And initialise all needed things.
	m_Rb = AddComponent<RigidBody>();
	m_Rb->GroundedStateChanged.AddListener(this, std::bind(&Character::ChangeAnimStyle, this, std::placeholders::_1));
	m_Rb->setGravityEnabled(true);

	//Set up collider and its collision mask.
	AddComponent<BoxCollider>()->SetUpCollider(LLGP::Vector2f(26, 38), LLGP::Vector2f(0, -3))->SetCollisionMask(collisionMask)->SetCollisionLayer(collisionLayer);

	SetBirdNumber(charBirdNumber);
	SetRiderColour(charRiderColour);

	GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Walking")->AddAnimation("Walk", 1, 4, LLGP::Vector2i(0, m_BirdNumber), LLGP::Vector2i(1, m_BirdNumber), LLGP::Vector2i(2, m_BirdNumber), LLGP::Vector2i(3, m_BirdNumber), LLGP::Vector2i(4, m_BirdNumber));
	GetComponent<AnimationManager>()->GetAnimationState<AnimationState>("Walking")->AddAnimation("Reverse", 0, 1, LLGP::Vector2i(4, m_BirdNumber));
	GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Flying")->AddAnimation("Fall", 0, 1, LLGP::Vector2i(6, m_BirdNumber));
	GetComponent<AnimationManager>()->GetAnimationState<AnimationState>("Flying")->AddAnimation("Flap", 0, 1, LLGP::Vector2i(5, m_BirdNumber));
	GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Flying");

	//-----------------------------------------------------------This has been removed for the general character class-------------------------------------------------------------//
	// AddComponent<PlayerInputController>()->getEvent<LLGP::Vector2<float>>("MoveDirection")->AddListener(this, std::bind(&Character::HandleInput, this, std::placeholders::_1)); //
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

	AddComponent<ScreenWrapper>();

	m_CanKillChar = true;
	this->onCollisionEnter.AddListener(this, std::bind(&Character::JoustResolution, this, std::placeholders::_1));
	g_OnFixedUpdate.AddListener(this, std::bind(&Character::FixedUpdate, this, std::placeholders::_1));

}

void Character::HandleInput(LLGP::Vector2f value)
{
	m_InputDirection = value;
	//std::cout << "Input Direction Change" << std::endl;
}

void Character::ChangeAnimStyle(bool isGrounded)
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

void Character::MovePlayer(float deltaTime)
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

	m_Rb->addForce(movementForce);
}

void Character::FixedUpdate(float deltaTime)
{
	MovePlayer(deltaTime);
	UpdateAnimation(deltaTime);
	RespawnTimer(deltaTime);
	RespawnImmunity(deltaTime);
}

void Character::RespawnImmunity(float deltaTime)
{
	if (GetName() == "Player")
	{
		//std::cout << m_CurrentRepsawnGrace << std::endl;
		//std::cout << m_CanKillChar << std::endl;
	}

	if (m_CanKillChar || !m_CharIsAlive) { return; }

	m_CurrentRepsawnGrace += deltaTime;
	if (m_CurrentRepsawnGrace >= 2.f)
	{
		std::cout << "Character Is once again Killable" << std::endl;
		m_CurrentRepsawnGrace = 0.f;
		m_CanKillChar = true;

		if (GetName() == "Player")
		{
			SetRiderColour('c');
		}
	}
}

void Character::SetRiderOffsets(bool grounded)
{
	m_RiderForward = 5;
	if (grounded)
	{
		switch (m_BirdNumber)
		{
		case 0:
			m_RiderHeight = 8;

			break;

		case 1:
			m_RiderHeight = 8;

			break;

		case 2:
			m_RiderHeight = 13;
			m_RiderForward = 5;

			break;

		default:
			m_RiderHeight = 8;

			break;
		}
	}
	else
	{
		switch (m_BirdNumber)
		{
		case 0:
			m_RiderHeight = 8;

			break;

		case 1:
			m_RiderHeight = 8;

			break;

		case 2:
			m_RiderHeight = 8;
			m_RiderForward = 5;

			break;

		default:
			m_RiderHeight = 8;

			break;
		}
	}
	
}

void Character::SetBirdNumber(int newBird)
{
	m_BirdNumber = newBird;
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

void Character::RespawnTimer(float deltaTime)
{
	if (m_CharIsAlive) { return; }

	m_CurrentRepsawnTimer += deltaTime;

	if (m_CurrentRepsawnTimer >= m_RespawnTime)
	{
		m_CharIsAlive = true;
		GetTransform()->setPosition(LLGP::Vector2f(460, 450));
		m_CurrentRepsawnTimer = 0;
	}
}

void Character::UpdateAnimation(float deltaTime)
{
	std::string animState = GetComponent<AnimationManager>()->ReturnActiveAnimationState();


#pragma region IsGrounded
	//If player is grounded do walky stuff
	if (m_Rb->IsGrounded())
	{
		if ((m_InputDirection.x > 0 && m_Rb->GetVelocity().x < 0) || (m_InputDirection.x < 0 && m_Rb->GetVelocity().x > 0))
		{
			m_Rb->setOpposingMovement(true);
		}
		else
		{
			m_Rb->setOpposingMovement(false);
		}

		if (m_Rb->GetOpposingMovement())
		{
			GetComponent<AnimationManager>()->GetAnimationState<AnimationState>(animState)->setActiveAnimation("Reverse");
		}
		else
		{
			GetComponent<AnimationManager>()->GetAnimationState<AnimationState>(animState)->setActiveAnimation("Walk");
		}

		if (m_Rb->GetOpposingMovement())
		{

		}
		else
		{
			if (m_InputDirection.x == 1)
			{
				GetComponent<SpriteRenderer>()->setFlipped(false);
				m_Rider->setFlipped(false);
			}
			else if (m_InputDirection.x == -1)
			{
				GetComponent<SpriteRenderer>()->setFlipped(true);
				m_Rider->setFlipped(true);
			}
		}
	}

#pragma endregion 
	//If the player isnt grounded, do flappy stuff
	if (!m_Rb->IsGrounded())
	{
		if (m_InputDirection.x == 1)
		{
			GetComponent<SpriteRenderer>()->setFlipped(false);
			m_Rider->setOffSet(LLGP::Vector2f(m_RiderForward, -m_RiderHeight))->setFlipped(false);
		}
		else if (m_InputDirection.x == -1)
		{
			GetComponent<SpriteRenderer>()->setFlipped(true);
			m_Rider->setOffSet(LLGP::Vector2f(-m_RiderForward, -m_RiderHeight))->setFlipped(true);
		}

		if (m_Rb->GetVelocity().y < 0 && m_InputDirection.y == 1)
		{
			GetComponent<AnimationManager>()->GetAnimationState<AnimationState>(animState)->setActiveAnimation("Flap");
		}
		else
		{
			GetComponent<AnimationManager>()->GetAnimationState<AnimationState>(animState)->setActiveAnimation("Fall");
		}
	}
	
	SetRiderOffsets(m_Rb->IsGrounded());

	if (m_Rider->getFlipped())
	{
		m_Rider->setOffSet(LLGP::Vector2f(-m_RiderForward, -m_RiderHeight));
	}
	else
	{
		m_Rider->setOffSet(LLGP::Vector2f(m_RiderForward, -m_RiderHeight));
	}
}

void Character::JoustResolution(CollisionInfo* info)
{
	//Check whether both colliders are on the joust collision bit layer ( the second bit from the right 0b000000>X<0)
	//If they are not, return.
	if (!((CHECK_BIT(info->collider->GetCollisionMask(), 1)) && (CHECK_BIT(info->otherCollider->GetCollisionLayer(), 1))))
	{
		return;
	}

	if (info->otherCollider->GetGameObject()->GetName() == "Player")
	{
		if (!static_cast<Character*>(info->otherCollider->GetGameObject())->m_CanKillChar)
		{
			return;
		}
	}

	if (!m_CharIsAlive || !m_CanKillChar)
	{
		return;
	}

	std::cout << "Jousted!" << std::endl;

	if ((info->collider->GetGameObject()->GetTransform()->returnPosition()).y < (info->otherCollider->GetGameObject()->GetTransform()->returnPosition()).y)
	{
		static_cast<Character*>(info->otherCollider->GetGameObject())->KillChar();
	}
	else
	{
		KillChar();
	}
}

void Character::SetRiderColour(char newRiderColour)
{
	m_RiderColour = newRiderColour;
	switch (m_RiderColour)
	{
	case 'y':
		m_ActualRiderColour = 0;
		break;
	case 'r':
		m_ActualRiderColour = 2;
		break;
	case 'b':
		m_ActualRiderColour = 6;
		break;
	case 'c':
		m_ActualRiderColour = 1;
		break;
	case 'g':
		m_ActualRiderColour = 4;
		break;
	default:
		break;
	}

	m_Rider->setUV(LLGP::Vector2i(m_ActualRiderColour, 3));
}

void Character::KillChar()
{
	m_CanKillChar = false;
	m_CharIsAlive = false;
	GetTransform()->setPosition(LLGP::Vector2f(450, -100));

	if (GetName() == "Player")
	{
		SetRiderColour('y');
	}
}

std::shared_ptr<Character> Character::CreateAICharacter(char characterColour, LLGP::Vector2f location)
{
	std::shared_ptr<Character> newAICharacter = std::make_unique<Character>();
	newAICharacter.get()->initialiseCharacter(2, characterColour, 0b00000011, 0b00000100);

	newAICharacter.get()->GetTransform()->setPosition(location);

	JoustAIController* controller = newAICharacter.get()->AddComponent<JoustAIController>();

	float maxSpeed = 100.f;

	switch (characterColour)
	{
	case 'r':
		controller->SetDifficultyVariables(15.f, 1.2f);
		maxSpeed = 75.f;
		break;
	case 'g':
		controller->SetDifficultyVariables(10.f, 1.7f);
		maxSpeed = 125.f;
		break;
	case 'b':
		controller->SetDifficultyVariables(6.f, 2.f);
		maxSpeed = 175.f;
		break;
	default:
		break;
	}

	newAICharacter.get()->GetComponent<RigidBody>()->SetMaxSpeed(maxSpeed);
	//newAICharacter.get()->AddComponent<DebugBox>()->SetUpDebugBox();

	return newAICharacter;
}

std::shared_ptr<Character> Character::CreatePlayerCharacter(LLGP::Vector2f location)
{
	std::shared_ptr<Character> newPlayerCharacter = std::make_unique<Character>();

	newPlayerCharacter.get()->initialiseCharacter(0, 'c', 0b00000111, 0b00000010);
	newPlayerCharacter.get()->AddComponent<PlayerInputController>()->getEvent<LLGP::Vector2<float>>("MoveDirection")->AddListener(newPlayerCharacter.get(), std::bind(&Character::HandleInput, newPlayerCharacter.get(), std::placeholders::_1));

	//newPlayerCharacter.get()->AddComponent<DebugBox>()->SetUpDebugBox();


	return newPlayerCharacter;
}
