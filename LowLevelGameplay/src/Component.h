#pragma once
#include <list>

class Component
{
public:
	std::list<Component> componentList;

	void AddComponent() {};
	void removeComponent() {};
	template<typename t>
	t getComponentInChildren(t type) { return; };
};
