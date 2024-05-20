#pragma once
#include <Object.h>
#include <string>
#include <vector>
#include <memory>
#include <isComponenet.h>
//#include <Transform.h>
#include <iostream>
#include <Event.h>

struct CollisionInfo;

class GameObject : public Object
{
public:
	GameObject();
	GameObject(const GameObject&) = default;

	LLGP::Event<CollisionInfo*> onCollisionEnter;
	LLGP::Event<CollisionInfo*> onCollisionStay;
	LLGP::Event<CollisionInfo*> onCollisionExit;
	
	inline void SetName(std::string newName) { m_Name = newName; }
	inline std::string GetName() { return m_Name; }

	void SetActive(bool newActive) { m_Active = newActive; }
	inline bool GetActive() { return m_Active; }

	inline void SetTag(std::string newTag) { m_Tag = newTag; }
	inline bool CompareTag(std::string comp) { return m_Tag == comp; }

	Transform2D* getTransform() { return transform; }


#pragma region ComponentManagement
	template<class T> requires isComponent<T>
	T* GetComponent()
	{
		T* returnComp = nullptr;

		for (int i = 0; i < m_Components.size(); i++)
		{
			returnComp = dynamic_cast<T*>(m_Components[i].get());
			if (returnComp != nullptr)
			{
				return returnComp;
			}
		}

		return nullptr;
	};

	template<class T> requires isComponent<T>
	std::vector<T*> GetComponents()
	{
		std::vector<T*> returnComps;

		for (int i = 0; i < m_Components.size(); i++)
		{
			if (T* comp = dynamic_cast<T*>(m_Components[i].get()))
			{
				returnComps.push_back(comp);
			}
		}

		return returnComps;
	};

	template<class T> requires isComponent<T> 
	T* AddComponent() 
	{
		m_Components.push_back(std::make_unique<T>(this));
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
	Transform2D* transform;
};
