#include <GameManager.h>
#include <BoxCollider.h>
#include <Collider.h>
#include <Transform.h>
#include <Platform.h>
#include <Cursor.h>
#include <GradExPlayer.h>
#include <Projectile.h>

GameManager::GameManager()
{
	StartLevelOne();
	static_cast<Projectile*>(getGameObjectByName("Projectile"))->EnableProjectile(LLGP::Vector2f(0.5f, -0.5f), 50.f, 1);
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
	newPlayerTest->SetActive(true);
	m_GameObjects.push_back(std::move(newPlayerTest));

	std::shared_ptr<Projectile> newProjectileTest = std::make_unique<Projectile>();
	newProjectileTest->GetTransform()->setPosition(LLGP::Vector2f(50, 450));
	newProjectileTest->EnableProjectile(LLGP::Vector2f(0.5f, -0.5f), 50.f, 1);
	newProjectileTest->SetTag("Projectile");
	newProjectileTest->SetName("Projectile");
	m_GameObjects.push_back(std::move(newProjectileTest));
#pragma region CreateAllPlatforms


#pragma endregion
}
