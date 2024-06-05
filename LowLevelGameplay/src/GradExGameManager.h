#pragma once
#include <GameManager.h>
#include <Event.h>

class Timer;

class GradExGameManager : public GameManager
{
public:
	GradExGameManager();
	~GradExGameManager();

	/// <summary>
	/// Call this function to respawn the player.
	/// </summary>
	/// <param name="playerIndex">The players index (controller number)</param>
	void RespawnPlayer(int playerIndex);

	/// <summary>
	/// Starts the level matching the inputed int. 
	/// </summary>
	/// <param name="levelNumber"></param>
	void StartLevel(int levelNumber);

	Timer* StartTimer(float timerLength, std::function<void(Timer*, int)> inFunc);

	void EndTimer(Timer* finishedTimer);

	void RespawnPlayerZero(Timer* timer, int required)
	{
		RespawnPlayer(0);
		EndTimer(timer);
	}

	void RespawnPlayerOne(Timer* timer, int required) 
	{
		RespawnPlayer(1);
		EndTimer(timer);
	}

	void CollectGarbage(float deltaTime);

	/// <summary>
	/// See: <seealso cref="GameManager::Start"/> for details
	/// </summary>
	void Start() override;

	LLGP::Event<int> LevelStarted;
	LLGP::Event<int> m_RespawnPlayer;
private:
	std::vector<Timer*> m_ActiveTimers;
	std::vector<Timer*> m_DestroyableTimers;
};
