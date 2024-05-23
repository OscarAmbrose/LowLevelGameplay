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

	// AI Characters starting positions

	// Easy enemies (r)
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(220, 60)));    // Near top-left platform
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(1700, 50)));   // Near top-right platform
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(340, 410)));   // Near middle-left platform
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(1540, 360)));  // Near middle-right platform
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(260, 740)));   // Near bottom-left platform
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(970, 80)));    // On new central floating platform
	m_GameObjects.push_back(Character::CreateAICharacter('r', LLGP::Vector2f(470, 930)));   // Near new bottom floating platform (left)

	// Medium enemies (g)
	m_GameObjects.push_back(Character::CreateAICharacter('g', LLGP::Vector2f(970, 210)));   // On central platform (top)
	m_GameObjects.push_back(Character::CreateAICharacter('g', LLGP::Vector2f(970, 470)));   // On central platform (bottom)
	m_GameObjects.push_back(Character::CreateAICharacter('g', LLGP::Vector2f(1350, 780)));  // Near floating platform (right-middle)
	m_GameObjects.push_back(Character::CreateAICharacter('g', LLGP::Vector2f(370, 150)));   // Near new floating platform (upper left)
	m_GameObjects.push_back(Character::CreateAICharacter('g', LLGP::Vector2f(1200, 540)));  // Near new mid-right platform
	m_GameObjects.push_back(Character::CreateAICharacter('g', LLGP::Vector2f(950, 880)));   // On new low-center platform
	m_GameObjects.push_back(Character::CreateAICharacter('g', LLGP::Vector2f(1390, 920)));  // Near new bottom floating platform (right)

	// Hard enemies (b)
	m_GameObjects.push_back(Character::CreateAICharacter('b', LLGP::Vector2f(1660, 690)));  // Near bottom-right platform
	m_GameObjects.push_back(Character::CreateAICharacter('b', LLGP::Vector2f(950, 710)));   // On additional floating platform (center)
	m_GameObjects.push_back(Character::CreateAICharacter('b', LLGP::Vector2f(600, 830)));   // Near floating platform (left-middle)
	m_GameObjects.push_back(Character::CreateAICharacter('b', LLGP::Vector2f(1520, 190)));  // Near new floating platform (upper right)
	m_GameObjects.push_back(Character::CreateAICharacter('b', LLGP::Vector2f(750, 580)));   // Near new mid-left platform
	m_GameObjects.push_back(Character::CreateAICharacter('b', LLGP::Vector2f(970, 470)));   // On central platform (bottom)
	m_GameObjects.push_back(Character::CreateAICharacter('b', LLGP::Vector2f(1540, 360)));  // Near middle-right platform


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
