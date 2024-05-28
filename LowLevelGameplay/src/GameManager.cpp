#include <GameManager.h>
#include <BoxCollider.h>
#include <Collider.h>
#include <Transform.h>
#include <Platform.h>
#include <Cursor.h>

GameManager::GameManager()
{
	StartLevelOne();
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

void GameManager::StartLevelOne()
{
	//Create player.


	std::shared_ptr<GameObject> newPlayerTest = std::make_unique<GameObject>();
	newPlayerTest.get()->AddComponent<Cursor>();
	m_GameObjects.push_back(std::move(newPlayerTest));

#pragma region CreateAllPlatforms


#pragma endregion
}
