#pragma once
#include <vector>
#include <memory>
#include <GameObject.h>
#include <isComponenet.h>
#include <SpriteRenderer.h>
#include <TestComponent.h>
#include <AnimationManager.h>
#include <PlayerInputController.h>
#include <Vector2.h>
#include <RigidBody.h>

class GameManager
{
public:
	GameManager();

	void testFunction(int i)
	{
		std::cout << i << std::endl;
	}

	void testFunction2(LLGP::Vector2<float> i)
	{
		meow = (LLGP::Vector2f(i.x, -i.y));
		if (i.x == -1)
		{
			GameObject* test = getGameObjectByName("Test");
			//test->GetComponent<AnimationManager>()->GetAnimationState<AnimationState>("Walking")->setActiveAnimation("Reverse");
		}
		else if (i.x == 1)
		{
			GameObject* test = getGameObjectByName("Test");
			test->GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Walking");
			//test->GetComponent<AnimationManager>()->GetAnimationState<AnimationState>("Walking")->setActiveAnimation("Walk");

		}
	}

	void fixedUpdate(float deltaTime)
	{
		float currentRotation = getGameObjectByName("Test")->getTransform()->returnRotation();
		LLGP::Vector2f location = getGameObjectByName("Test")->getTransform()->returnPosition();

		RigidBody* rb = getGameObjectByName("Test")->GetComponent<RigidBody>();
		LLGP::Vector2f velocity = rb->GetVelocity();
		std::string animState = getGameObjectByName("Test")->GetComponent<AnimationManager>()->ReturnActiveAnimationState();

		if ((meow.x > 0 && velocity.x < 0) || (meow.x < 0 && velocity.x > 0))
		{
			rb->setOpposingMovement(true);
		}
		else
		{
			rb->setOpposingMovement(false);
		}

		if (rb->GetOpposingMovement())
		{
			getGameObjectByName("Test")->GetComponent<AnimationManager>()->GetAnimationState<AnimationState>(animState)->setActiveAnimation("Reverse");
		}
		else
		{
			getGameObjectByName("Test")->GetComponent<AnimationManager>()->GetAnimationState<AnimationState>(animState)->setActiveAnimation("Walk");
		}
		
		if (rb->GetOpposingMovement())
		{

		}
		else
		{
			if (meow.x == 1)
			{
				getGameObjectByName("Test")->GetComponent<SpriteRenderer>()->setFlipped(false);
			}
			else if (meow.x == -1)
			{
				getGameObjectByName("Test")->GetComponent<SpriteRenderer>()->setFlipped(true);
			}
		}
		
		//getGameObjectByName("Test")->getTransform()->setPosition(LLGP::Vector2f(location.x + meow.x, location.y + -meow.y));

		LLGP::Vector2f movementForce;
		float movementSpeed = 200.f;

		movementForce = meow * movementSpeed;

		getGameObjectByName("Test")->GetComponent<RigidBody>()->addForce(movementForce);
	}

	~GameManager() {};

	template<class T> requires isComponent<T>
	std::vector<T*> getAllComponentsOfType()
	{
		std::vector<T*> gatheredList;

		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			if (auto gameObject = m_GameObjects[i]) // Check if gameObject is not null
			{
				T* discoveredComponent = gameObject->GetComponent<T>();
				if (discoveredComponent != nullptr)
				{
					gatheredList.push_back(discoveredComponent);
				}
			}
		}
		return gatheredList;
	}

	GameObject* getGameObjectByName(std::string objectTag);



private:
	int m_LevelNumber = 0;

public:
	std::vector<std::shared_ptr<GameObject>> m_GameObjects;

	LLGP::Vector2f meow = Vector2f(0.f,0.f);
	//SpriteRenderer* srTesting;
	//SpriteRenderer* srTesting2;
};
