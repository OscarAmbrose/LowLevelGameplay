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

	void Start() override { /*std::cout << "Start in Game Obj" << std::endl;*/ };
	void Update() override { UpdateComponents(); };
	void FixedUpdate() override { FixedUpdateComponents(); };
	
	inline void SetName(std::string newName) { m_Name = newName; }
	inline std::string GetName() { return m_Name; }

	void SetActive(bool newActive) { m_Active = newActive; }
	inline bool GetActive() { return m_Active; }

	inline void SetTag(std::string newTag) { m_Tag = newTag; }
	inline bool CompareTag(std::string comp) { return m_Tag == comp; }

	void UpdateComponents()
	{
		Object* objectToBeUpdated;
		for (int i = 0; i < m_Components.size(); i++)
		{
			objectToBeUpdated = m_Components[i].get();
			objectToBeUpdated->Update();
		}
		objectToBeUpdated = NULL;
		delete(objectToBeUpdated);
	}

	void FixedUpdateComponents()
	{
		Object* objectToBeUpdated;
		for (int i = 0; i < m_Components.size(); i++)
		{
			objectToBeUpdated = m_Components[i].get();
			objectToBeUpdated->FixedUpdate();
		}
		objectToBeUpdated = NULL;
		delete(objectToBeUpdated);
	}

	inline Transform2D* getTransform() { return transform.get(); }

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

	

	template<class T> requires isComponent<T> T* AddComponent() {
		std::unique_ptr<Component> newComp = std::make_unique<T>(this, transform.get());
		m_Components.push_back(std::move(newComp));
		return static_cast<T*>(m_Components[m_Components.size()-1].get());
	};

	template<class T> requires isComponent<T> bool RemoveComponent(T* comp)
	{
		bool returnBool;
		//GetComponent<T>
		for (int i = 0; i < m_Components.size(); i++)
		{
			T* returnComp = dynamic_cast<T*>(m_Components[i].get());
			if (returnComp != nullptr)
			{
				returnBool = true;
				m_Components.erase(i);
				break;
			}
			returnBool = false;
		}
	};

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
