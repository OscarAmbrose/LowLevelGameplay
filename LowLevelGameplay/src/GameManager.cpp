#include <GameManager.h>
#include <BoxCollider.h>
#include <Collider.h>
#include <Transform.h>
#include <Platform.h>
#include <Cursor.h>
#include <GradExPlayer.h>
#include <Projectile.h>
#include <DebugBox.h>

GameManager::GameManager()
{
	StartLevelOne();
}

GameManager::~GameManager()
{
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
	newPlayerTest->GetTransform()->SetPosition(LLGP::Vector2f(50.f, 100.f));
	newPlayerTest->SetActive(true);
	m_GameObjects.push_back(std::move(newPlayerTest));

	m_GameObjects.push_back(Platform::CreateCeiling());
	auto floor = Platform::CreateCeiling();
	floor->GetTransform()->SetPosition(LLGP::Vector2f(960.f, 1070.f));
	m_GameObjects.push_back(floor);
#pragma region CreateAllPlatforms


#pragma endregion
}
