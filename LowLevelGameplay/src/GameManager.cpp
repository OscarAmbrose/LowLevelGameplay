#include <GameManager.h>
#include <BoxCollider.h>
#include <Collider.h>
#include "Transform.h"
#include <DebugBox.h>
#include <JoustPlayerCharacter.h>
#include <JoustCharacter.h>
#include <Platform.h>
#include <PlayerDeathHandler.h>



GameManager::GameManager()
{
	PlayerDeathHandler::RegisterGameManager(this);


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
	std::shared_ptr<GameObject> player = std::make_shared<JoustPlayer>();
	player.get()->SetName("Player");
	player.get()->GetTransform()->setPosition(LLGP::Vector2f(928, 400));

	m_GameObjects.push_back(std::move(player));

	m_GameObjects.push_back(Platform::CreateCeiling());

#pragma region CreateAllPlatforms

	// Top-left platform
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(200, 90)));

	m_GameObjects.push_back(Character::CreateAICharacter('g', LLGP::Vector2f(200, 30)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(400, 30)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(100, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(300, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(500, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(600, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(700, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(850, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(750, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(110, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 530)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 130)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 930)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 230)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 430)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(800, 630)));

	// Top-right platform
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(1720, 80)));

	// Middle-left platform
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(320, 440)));

	// Middle-right platform
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(1560, 390)));

	// Bottom-left platform
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(240, 770)));

	// Bottom-right platform
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(1680, 720)));

	// Central platform (top)
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(950, 240)));

	// Central platform (bottom)
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(950, 500)));

	// Floating platform (left-middle)
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(580, 860)));

	// Floating platform (right-middle)
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(1370, 810)));

	// Additional floating platform (center)
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(930, 740)));

	// New floating platform (upper left)
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(350, 180)));

	// New floating platform (upper right)
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(1540, 220)));

	// New central floating platform
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(950, 110)));

	// New mid-left platform
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(730, 610)));

	// New mid-right platform
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(1220, 570)));

	// New low-center platform
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(930, 910)));

	// New bottom floating platform (left)
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(450, 960)));

	// New bottom floating platform (right)
	m_GameObjects.push_back(Platform::CreatePlatformType1(LLGP::Vector2f(1410, 950)));


#pragma endregion
}
