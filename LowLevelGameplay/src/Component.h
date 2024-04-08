#pragma once
#include <list>
#include <SameClassConcept.h>
#include<iostream>
#include <Updatable.h>

class Component : public Updatable
{
public:
	Component();
	~Component();

	void setParent(Component* parentComponent);

	void makeDirtyFlag();

	void removeAllComponents();
	void removeComponent(Component* componentToRemove);

	void debugPrint();

	Component* returnCompID();

	void AddComponent(Component* component);

	std::list<Component*> componentList;
	std::list<Component*>::iterator it;

	bool toBeDeleted;

	//template<class T> 
	//void AddComponent(T ComponentType);

	template<class T> requires SameClassConcept<T>
	T* getComponentInChildren(T type);

	Component* parent;
};

//template<class T> 
//inline void Component::AddComponent(T ComponentType)
//{
//	componentList.push_back(&ComponentType);
//	it = componentList.begin();
//
//	Component* b = ComponentType;
//	b->debugPrint();
//}

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
