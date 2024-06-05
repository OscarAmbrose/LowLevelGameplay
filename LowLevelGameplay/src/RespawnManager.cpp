#include "RespawnManager.h"
#include <GradExPlayer.h>
#include <GradExGameManager.h>
#include <Transform.h>

std::vector<HealthComponent*> HealthComponents;

void RespawnManager::PlayerDied(GameObject* player)
{
	GradExGameManager* _GM = static_cast<GradExGameManager*>(GameManager::instance);
	PlayerCharacter* _Player;
	if (!(_Player = dynamic_cast<PlayerCharacter*>(player))) { return; }

	float respawnTime = _Player->GetComponent<HealthComponent>()->GetRespawnTimer();

	switch (_Player->GetPlayerNumber())
	{
	case 0:
		_GM->StartTimer(respawnTime, std::bind(&GradExGameManager::RespawnPlayerZero, _GM, std::placeholders::_1, std::placeholders::_2));
		break;
	case 1:
		_GM->StartTimer(respawnTime, std::bind(&GradExGameManager::RespawnPlayerOne, _GM, std::placeholders::_1, std::placeholders::_2));
		break;
	default:
		break;
	}
}

