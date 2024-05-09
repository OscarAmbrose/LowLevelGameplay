#pragma once
#include <vector>
#include <memory>
#include <GameObject.h>
#include <isComponenet.h>
#include <SpriteRenderer.h>
#include <TestComponent.h>
#include <AnimationManager.h>
#include <PlayerController.h>
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

		PlayerInputController* PC = testScoper->AddComponent<PlayerInputController>();

		//InputManager* inputManagerTest = testScoper->AddComponent<InputManager>();
		//inputManagerTest->addEvent<InputAsset<int>>("TestEvent");
		//inputManagerTest->getEvent<int>("TestEvent")->AddListener(this, std::bind(&GameManager::testFunction, this, std::placeholders::_1));
		//inputManagerTest->GetInputAction<InputAsset<int>>("TestEvent")->CallEvent(5);

		//inputManagerTest->addEvent<InputAsset<LLGP::Vector2i>>("TestEvent2");
		//inputManagerTest->getEvent<LLGP::Vector2i>("TestEvent2")->AddListener(this, std::bind(&GameManager::testFunction2, this, std::placeholders::_1));
		//inputManagerTest->invokeEvent<LLGP::Vector2i>("TestEvent2", LLGP::Vector2i(5, 0));

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

	void testFunction2(LLGP::Vector2i i)
	{
		std::cout << i.x << ", " << i.y << std::endl;
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

};
