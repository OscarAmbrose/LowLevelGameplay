#include <GameManager.h>
#include <Transform.h>

GameManager* GameManager::instance;


GameManager::GameManager()
{
	if (GameManager::instance != nullptr)
	{
		delete this;
		return;
	}
	GameManager::instance = this;
}

GameManager::~GameManager()
{
}

GameObject* GameManager::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
	if (gameObject.get()->GetName() == "")
	{
		throw std::invalid_argument("Game Object was not given a name");
		return nullptr;
	}

	m_GameObjects.push_back(std::move(gameObject));
	return dynamic_cast<GameObject*>(m_GameObjects[m_GameObjects.size() - 1].get());
}

GameObject* GameManager::GetGameObjectByName(std::string objectName)
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i]->GetName() == objectName)
		{
			return m_GameObjects[i].get();
			break;
		}
	}
	return nullptr;
}

void GameManager::ClearGameObjects()
{
	m_GameObjects.clear();
}
