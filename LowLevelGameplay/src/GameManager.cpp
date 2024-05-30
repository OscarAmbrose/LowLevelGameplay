#include <GameManager.h>
#include <BoxCollider.h>
#include <Collider.h>
#include <Transform.h>
#include <Platform.h>
#include <Cursor.h>
#include <GradExPlayer.h>

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


	std::shared_ptr<PlayerCharacter> newPlayerTest = std::make_unique<PlayerCharacter>(0);
	m_GameObjects.push_back(std::move(newPlayerTest));

#pragma region CreateAllPlatforms


#pragma endregion
}
