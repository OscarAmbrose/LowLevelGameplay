#pragma once
#include <list>
#include <SameClassConcept.h>
#include<iostream>

class Component
{
public:
	Component();

	void removeComponent();

	void debugPrint();

	std::list<Component*> componentList;
	std::list<Component*>::iterator it;

	template<class T> 
	void AddComponent(T ComponentType);

	template<class T> requires SameClassConcept<T>
	T* getComponentInChildren(T type);
};

template<class T> 
inline void Component::AddComponent(T ComponentType)
{

}

template<class T> requires SameClassConcept<T>
T* Component::getComponentInChildren(T type)
{
	for (int i = 0; i < componentList.size(); i++) 
	{
		if (dynamic_cast<T*>(componentList[i]) != nullptr)
		{
			return componentList[i];
		}
	}
	return nullptr;
}

class testClass : public Component
{
public:
	testClass();

};
