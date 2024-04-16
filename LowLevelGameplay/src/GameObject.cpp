#pragma once
#include <GameObject.h>
#include <vector>

GameObject::GameObject()
{
	SetActive(true);
}

//template<class T> requires isComponent<T>
//inline T* GameObject::GetComponent()
//{
//	T* returnComp = nullptr;
//
//	for (int i = 0; i < m_Components.size(); i++)
//	{
//		returnComp = static_cast<T*>(m_Components[i].get());
//		if (returnComp != nullptr)
//		{
//			break;
//		}
//	}
//
//	return returnComp;
//}

//template<class T> requires isComponent<T>
//T* GameObject::AddComponent()
//{
//	std::unique_ptr<Component> newComp = std::make_unique<T>(this);
//	m_Components.push_back(std::move(newComp));
//	return static_cast<T*>(m_Components[m_Components.size()].get());
//}

//template<class T> requires isComponent<T>
//bool GameObject::RemoveComponent(T* comp)
//{
//	bool returnBool;
//	for (int i = 0; i < m_Components.size(); i++)
//	{
//		T* returnComp = static_cast<T*>(m_Components[i].get());
//		if (returnComp != nullptr)
//		{
//			returnBool = true;
//			m_Components.erase(i);
//			break;
//		}
//		returnBool = false;
//	}
//}
