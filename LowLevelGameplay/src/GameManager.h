#pragma once
#include <vector>
#include <memory>
#include <GameObject.h>
#include <isComponenet.h>
#include <SpriteRenderer.h>
#include <AnimationManager.h>
#include <Vector2.h>
#include <RigidBody.h>
#include <BoxCollider.h>

class GameManager
{
public:
	GameManager();

	~GameManager();

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

	void StartLevelOne();

private:
	int m_LevelNumber = 0;

public:
	std::vector<std::shared_ptr<GameObject>> m_GameObjects;

	LLGP::Vector2f TestInputDirection = LLGP::Vector2f(0.f,0.f);
	//SpriteRenderer* srTesting;
	//SpriteRenderer* srTesting2;
};
