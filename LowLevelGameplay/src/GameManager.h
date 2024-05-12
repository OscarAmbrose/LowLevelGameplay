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

class GameManager
{
public:
	GameManager()
	{
		//WARNING -- HORRIBLE MESS OF TESTING, DO NOT OPEN!!!!!

#pragma region TESTING MESS DO NOT OPEN
		std::shared_ptr<GameObject> testScoper = std::make_shared<GameObject>();
		std::shared_ptr<GameObject> testScoper2 = std::make_shared<GameObject>();
		std::shared_ptr<GameObject> gameObjectExample2 = std::make_shared<GameObject>();
		std::shared_ptr<GameObject> gameObjectExample1 = std::make_shared<GameObject>();
		std::shared_ptr<GameObject> testScoper5 = std::make_shared<GameObject>();

		g_OnFixedUpdate.AddListener(this, std::bind(&GameManager::fixedUpdate, this, std::placeholders::_1));

		testScoper->AddComponent<SpriteRenderer>();
		testScoper->AddComponent<AnimationManager>();
		gameObjectExample2->AddComponent<SpriteRenderer>();
		gameObjectExample1->AddComponent<SpriteRenderer>();
		testScoper5->AddComponent<SpriteRenderer>();
		testScoper2->AddComponent<SpriteRenderer>();

		gameObjectExample1->GetComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(14, 7));
		gameObjectExample2->GetComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(6, 10), LLGP::Vector2i(176, 18));
		testScoper5->GetComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(17, 7));

		gameObjectExample2->getTransform()->setPosition(LLGP::Vector2f(462, 180));
		gameObjectExample1->getTransform()->setPosition(LLGP::Vector2f(450, 225));
		testScoper5->getTransform()->setPosition(LLGP::Vector2f(461, 225));
		testScoper2->getTransform()->setPosition(LLGP::Vector2f(458, 272));
		
		testScoper->GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Walking")->AddAnimation("Walk", 1, 4, Vector2i(0, 2), Vector2i(1, 2), Vector2i(2, 2), Vector2i(3, 2), Vector2i(4, 2));
		testScoper->GetComponent<AnimationManager>()->GetAnimationState<AnimationState>("Walking")->AddAnimation("Reverse", 0, 1, Vector2i(4, 2));
		//testScoper->GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Walking2")->AddAnimation("Walk", 0, 1, Vector2i(5, 2));
		testScoper->GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Walking");

		testScoper->AddComponent<PlayerInputController>()->getEvent<LLGP::Vector2<float>>("MoveDirection")->AddListener(this, std::bind(&GameManager::testFunction2, this, std::placeholders::_1));


		testScoper->SetName("Test");
		testScoper2->SetName("Test 2");
		testScoper->SetTag("Debug Object");

		m_GameObjects.push_back(std::move(testScoper));
		m_GameObjects.push_back(std::move(testScoper2));
		m_GameObjects.push_back(std::move(gameObjectExample2));
		m_GameObjects.push_back(std::move(gameObjectExample1));
		m_GameObjects.push_back(std::move(testScoper5));
#pragma endregion

		//WARNING -- HORRIBLE MESS OF TESTING, DO NOT OPEN!!!!!
	};

	void testFunction(int i)
	{
		std::cout << i << std::endl;
	}

	void testFunction2(LLGP::Vector2<float> i)
	{
		meow = i;
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
		if (meow.x == 1)
		{
			getGameObjectByName("Test")->GetComponent<SpriteRenderer>()->setFlipped(false);
		}
		else if (meow.x == -1)
		{
			getGameObjectByName("Test")->GetComponent<SpriteRenderer>()->setFlipped(true);
		}
		
		getGameObjectByName("Test")->getTransform()->setPosition(LLGP::Vector2f(location.x + meow.x, location.y + -meow.y));

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
