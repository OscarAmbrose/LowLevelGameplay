#pragma once
#include <GradExGameManager.h>
#include <BoxCollider.h>
#include <Transform.h>
#include <Platform.h>
#include <Cursor.h>
#include <GradExPlayer.h>
#include <Projectile.h>
#include <SpriteRenderer.h>
#include <Timer.h>
#include <HealthComponent.h>
#include <string>
#include <functional>
#include <memory>

GradExGameManager::GradExGameManager() : GameManager()
{
	g_OnCollectGarbage.AddListener(this, std::bind(&GradExGameManager::CollectGarbage, this, std::placeholders::_1));
}

GradExGameManager::~GradExGameManager()
{
	g_OnCollectGarbage.RemoveListener(this, std::bind(&GradExGameManager::CollectGarbage, this, std::placeholders::_1));
}

void GradExGameManager::RespawnPlayer(int playerIndex)
{
	std::string playerName = "Player"+std::to_string(playerIndex);
	if (auto object = GetGameObjectByName(playerName)) { object->GetComponent<HealthComponent>()->Respawn(); }
}

void GradExGameManager::StartLevel(int levelNumber)
{
	//Create player.
	AddGameObject<PlayerCharacter>()->SetPlayerNumber(0)->InitialiseCharacter()->SetName("Player0");
	GetGameObjectByName("Player0")->GetTransform()->SetPosition(LLGP::Vector2f(100.f, 450.f));

	//Create second player.
	AddGameObject<PlayerCharacter>()->SetPlayerNumber(1)->InitialiseCharacter()->SetName("Player1");
	GetGameObjectByName("Player1")->GetTransform()->SetPosition(LLGP::Vector2f(1700.f, 450.f));
	GetGameObjectByName("Player1")->GetComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(3, 3));
	GetGameObjectByName("Player1")->GetComponent<Cursor>()->m_SpriteRenderer->setUV(LLGP::Vector2i(11, 2));

	StartTimer(1.f, std::bind(&GradExGameManager::RespawnPlayerOne, this, std::placeholders::_1, std::placeholders::_2));

#pragma region CreateMapBounds
	//Create floor and ceiling objs
	auto ceiling = Platform::CreateCeiling();
	ceiling.get()->SetName("Ceiling");
	AddGameObject(ceiling);

	//Floor
	auto floor = Platform::CreateCeiling();
	floor->GetTransform()->SetPosition(LLGP::Vector2f(960.f, 1100.f));
	floor->SetName("Floor");
	AddGameObject(floor);
#pragma endregion
}

Timer* GradExGameManager::StartTimer(float timerLength, std::function<void(Timer*, int)> inFunc)
{
	Timer* newTimer = new Timer(timerLength);
	newTimer->TimerFinished.AddListener(this, inFunc);
	newTimer->StartTimer(timerLength);
	m_ActiveTimers.push_back(std::move(newTimer));
	return (m_ActiveTimers[m_ActiveTimers.size() - 1]);
}

void GradExGameManager::EndTimer(Timer* finishedTimer)
{
	m_DestroyableTimers.push_back(finishedTimer);
}

void GradExGameManager::CollectGarbage(float deltaTime)
{
	for (Timer* timer : m_DestroyableTimers)
	{
		bool timerFound = false;
		for (int timerIndex = 0; timerIndex < m_ActiveTimers.size(); timerIndex++)
		{
			if (m_ActiveTimers[timerIndex] == timer)
			{
				g_OnUpdate.RemoveListener(m_ActiveTimers[timerIndex], std::bind(&Timer::Update, m_ActiveTimers[timerIndex], std::placeholders::_1));
				m_ActiveTimers[timerIndex]->TimerFinished.Empty();
				delete m_ActiveTimers[timerIndex];
				m_ActiveTimers.erase(m_ActiveTimers.begin() + timerIndex);
				timerFound = true;
				break;
			}
		}
		if (!timerFound) { throw std::invalid_argument("Timer was not found, memory leak detected."); }
	}
	m_DestroyableTimers.erase(m_DestroyableTimers.begin(), m_DestroyableTimers.end());
}

void GradExGameManager::Start()
{
	StartLevel(1);
}
