#pragma once
#include <Object.h>
#include <string>
#include <vector>
#include <memory>
#include <isComponenet.h>
//#include <Transform.h>
#include <iostream>

class GameObject : public Object
{
public:
	GameObject();
	GameObject(const GameObject&) = default;


	
	inline void SetName(std::string newName) { m_Name = newName; }
	inline std::string GetName() { return m_Name; }

	void SetActive(bool newActive) { m_Active = newActive; }
	inline bool GetActive() { return m_Active; }

	inline void SetTag(std::string newTag) { m_Tag = newTag; }
	inline bool CompareTag(std::string comp) { return m_Tag == comp; }

	Transform2D* getTransform() { return transform.get(); }


#pragma region ComponentManagement
	template<class T> requires isComponent<T> T* GetComponent()
	{
		T* returnComp = nullptr;

		for (int i = 0; i < m_Components.size(); i++)
		{
			returnComp = dynamic_cast<T*>(m_Components[i].get());
			if (returnComp != nullptr)
			{
				break;
			}
		}

		return returnComp;
	};

	template<class T> requires isComponent<T> 
	T* AddComponent() 
	{
		std::unique_ptr<Component> newComp = std::make_unique<T>(this);
		m_Components.push_back(std::move(newComp));
		return dynamic_cast<T*>(m_Components[m_Components.size()-1].get());
	};

	template<class T> requires isComponent<T> 
	bool RemoveComponent()
	{
		bool returnBool = false;
		T* returnComp = nullptr;

		for (int i = 0; i < m_Components.size(); i++)
		{
			returnComp = dynamic_cast<T*>(m_Components[i].get());
			if (returnComp != nullptr)
			{
				returnBool = true;
				m_Components.erase(m_Components.begin() + i);
				//m_Components.erase(dynamic_cast<T*>(m_Components[i].get()));
				break;
			}
			returnBool = false;
		}
		return returnBool;
	};
#pragma endregion


private:
	std::string m_Name;
	bool m_Active;
	std::string m_Tag;
	std::vector<std::unique_ptr<Component>> m_Components;

public:
	std::unique_ptr<Transform2D> transform = std::make_unique<Transform2D>();
	inline bool operator==(const GameObject& other) { return this->uuid == other.uuid; }
	inline bool operator!=(const GameObject& other) { return !(*this == other); }
};
