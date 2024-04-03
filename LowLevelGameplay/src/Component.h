#pragma once
#include <list>
#include <SameClassConcept.h>

class Component
{
public:
	Component();

	std::list<Component&> componentList;

	void AddComponent();
	void removeComponent();

	template<class T> requires SameClassConcept<T>
	T getComponentInChildren(T type);
};

template<class T> requires SameClassConcept<T>
inline T Component::getComponentInChildren(T Class)
{
	T& value = null;
	for (int i = 0; i < componentList.size(); i++) 
	{
		if (componentList[i].class == Class) 
		{
			value = componentList[i].value;
			break;
		}
	}
	return value;
}
