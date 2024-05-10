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
		std::shared_ptr<GameObject> testScoper = std::make_shared<GameObject>();
		std::shared_ptr<GameObject> testScoper2 = std::make_shared<GameObject>();

		testScoper->AddComponent<SpriteRenderer>();

		testScoper->AddComponent<AnimationManager>();

		testScoper->GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Walking")->AddAnimation("Walk", 1, 4, Vector2i(0, 2), Vector2i(1, 2), Vector2i(2, 2), Vector2i(3, 2), Vector2i(4, 2));
		testScoper->GetComponent<AnimationManager>()->addAnimationState<AnimationState>("Walking2")->AddAnimation("Walk", 0, 1, Vector2i(5, 2));
		testScoper->GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Walking");

		testScoper->AddComponent<PlayerInputController>()->getEvent<LLGP::Vector2<float>>("MoveDirection")->AddListener(this, std::bind(&GameManager::testFunction2, this, std::placeholders::_1));

		testScoper2->AddComponent<SpriteRenderer>();


		testScoper->SetName("Test");
		testScoper2->SetName("Test 2");
		testScoper->SetTag("Debug Object");

		testScoper2->getTransform()->setPosition(Vector2<float>(testScoper2->getTransform()->returnPosition().x + 10, 300));

		m_GameObjects.push_back(std::move(testScoper));
		m_GameObjects.push_back(std::move(testScoper2));
	};

	void testFunction(int i)
	{
		std::cout << i << std::endl;
	}

	void testFunction2(LLGP::Vector2<float> i)
	{
		if (i.x == -1)
		{
			getGameObjectByName("Test")->GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Walking2");
		}
		else if (i.x == 1)
		{
			GameObject* test = getGameObjectByName("Test");
			test->GetComponent<AnimationManager>()->setActiveAnimationState<AnimationState>("Walking");
		}
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

	//SpriteRenderer* srTesting;
	//SpriteRenderer* srTesting2;
};
