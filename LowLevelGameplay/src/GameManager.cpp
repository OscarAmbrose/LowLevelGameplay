#include <GameManager.h>
#include <BoxCollider.h>
#include <Collider.h>
#include <Transform.h>
#include <Platform.h>

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

#pragma region CreateAllPlatforms


#pragma endregion
}
