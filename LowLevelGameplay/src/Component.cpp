#pragma once
#include "Component.h"


Component::Component()
{
	testClass meow = testClass();
	Component* now = &meow;
	componentList.push_back(now);
}

void Component::removeComponent()
{

}

