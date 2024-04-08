#pragma once
#include "Component.h"


Component::Component()
{
	parent = this;
	toBeDeleted = false;
}

Component::~Component()
{
	removeAllComponents();
	//delete[] parent;
}

void Component::setParent(Component* parentComponent)
{
	parent = parentComponent;
}

void Component::removeAllComponents()
{
	std::cout << "Removing all components..." << std::endl;
	std::cout << componentList.size() << std::endl;

	for (auto It = componentList.begin(); It != componentList.end(); ++It)
	{
		//deconstruct component
		(*It)->removeAllComponents();
	}
	componentList.clear();
	std::cout << componentList.size() << std::endl;
}

void Component::makeDirtyFlag()
{
	toBeDeleted = true;
}

void Component::removeComponent(Component* componentToRemove)
{
	for (auto Bit = componentList.begin(); Bit != componentList.end(); ++Bit)
	{
		//Remove component if it is the same as the other component
		if (*Bit == componentToRemove)
		{
			//remove component from list
			componentList.erase(Bit);
			//deconstruct component
			(*Bit)->removeAllComponents();
			break;
		}
	}
}

void Component::debugPrint()
{
	std::cout << "Hey Im alive!!";
}

Component* Component::returnCompID()
{
	return this;
}

void Component::AddComponent(Component* component)
{
	componentList.insert(componentList.begin(), component);
	component->setParent(this);
}


