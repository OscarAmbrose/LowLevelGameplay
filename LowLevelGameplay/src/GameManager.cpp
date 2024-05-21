#include <GameManager.h>
#include <BoxCollider.h>
#include <Collider.h>
#include "Transform.h"


GameManager::GameManager()
{
	{
		//WARNING -- HORRIBLE MESS OF TESTING, DO NOT OPEN!!!!!

#pragma region TESTING MESS DO NOT OPEN
		std::shared_ptr<GameObject> testScoper = std::make_shared<GameObject>();
		std::shared_ptr<GameObject> testScoper2 = std::make_shared<GameObject>();
		std::shared_ptr<GameObject> gameObjectExample2 = std::make_shared<GameObject>();
		std::shared_ptr<GameObject> gameObjectExample1 = std::make_shared<GameObject>();
		std::shared_ptr<GameObject> testScoper5 = std::make_shared<GameObject>();

		g_OnFixedUpdate.AddListener(this, std::bind(&GameManager::fixedUpdate, this, std::placeholders::_1));

		testScoper->AddComponent<SpriteRenderer>()->setRenderLayer(1);
		testScoper->AddComponent<AnimationManager>();
		gameObjectExample2->AddComponent<SpriteRenderer>()->setRenderLayer(0);
		gameObjectExample1->AddComponent<SpriteRenderer>()->setRenderLayer(0);
		testScoper5->AddComponent<SpriteRenderer>()->setRenderLayer(0);
		testScoper2->AddComponent<SpriteRenderer>()->setRenderLayer(0);

		gameObjectExample1->GetComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(14, 7));
		gameObjectExample2->GetComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(6, 10), LLGP::Vector2i(176, 18));

		testScoper5->GetComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(17, 7));

		testScoper->AddComponent<RigidBody>();
		testScoper->AddComponent<BoxCollider>();

		gameObjectExample2->getTransform()->setPosition(LLGP::Vector2f(462, 180));
		gameObjectExample1->getTransform()->setPosition(LLGP::Vector2f(450, 225));
		testScoper5->getTransform()->setPosition(LLGP::Vector2f(461, 225));
		testScoper2->getTransform()->setPosition(LLGP::Vector2f(458, 272));

		testScoper->GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Walking")->AddAnimation("Walk", 1, 4, LLGP::Vector2i(0, 0), LLGP::Vector2i(1, 0), LLGP::Vector2i(2, 0), LLGP::Vector2i(3, 0), LLGP::Vector2i(4, 0));
		testScoper->GetComponent<AnimationManager>()->GetAnimationState<AnimationState>("Walking")->AddAnimation("Reverse", 0, 1, LLGP::Vector2i(4, 0));
		//testScoper->GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Walking2")->AddAnimation("Walk", 0, 1, Vector2i(5, 2));
		testScoper->GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Walking");

		testScoper->AddComponent<PlayerInputController>()->getEvent<LLGP::Vector2<float>>("MoveDirection")->AddListener(this, std::bind(&GameManager::testFunction2, this, std::placeholders::_1));


		testScoper->SetName("Test");
		testScoper2->SetName("Test 2");
		testScoper->SetTag("Debug Object");

		//testScoper->AddComponent<BoxCollider>()->setUpCollider(LLGP::Vector2i(0,0));


		m_GameObjects.push_back(std::move(testScoper));
		m_GameObjects.push_back(std::move(testScoper2));
		m_GameObjects.push_back(std::move(gameObjectExample2));
		m_GameObjects.push_back(std::move(gameObjectExample1));
		m_GameObjects.push_back(std::move(testScoper5));
#pragma endregion
		//WARNING -- HORRIBLE MESS OF TESTING, DO NOT OPEN!!!!!
	}
}

void GameManager::fixedUpdate(float deltaTime)
{
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
}

GameObject* GameManager::getGameObjectByName(std::string objectTag)
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i]->GetName() == objectTag)
		{
			return m_GameObjects[i].get();
			break;
		}
	}
	return nullptr;
}
