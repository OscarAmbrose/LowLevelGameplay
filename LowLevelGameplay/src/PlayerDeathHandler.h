#pragma once


class GameManager;

class PlayerDeathHandler
{
public:
	PlayerDeathHandler() = delete;

	static void RegisterGameManager(GameManager* gm);
	static void DeregisterGameManager();

private:
	static GameManager* _GameManager;
};
