#pragma once
#include "Component.h"


Component::Component()
{
	
}

void Component::removeComponent()
{
	testClass meow = testClass();
	Component* now = &meow;
	componentList.push_back(now);
	it = componentList.begin();

	Component* b = *it;
	b->debugPrint();
}

void Component::debugPrint()
{
	std::cout << "Hey Im alive!!";
}


