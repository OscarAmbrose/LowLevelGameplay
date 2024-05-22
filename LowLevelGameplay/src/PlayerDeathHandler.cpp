#include <PlayerDeathHandler.h>
#include <GameManager.h>

GameManager* PlayerDeathHandler::_GameManager;

void PlayerDeathHandler::RegisterGameManager(GameManager* gm)
{
	_GameManager = gm;
}

void PlayerDeathHandler::DeregisterGameManager()
{
	_GameManager = nullptr;
}
