#pragma once
#include <Object.h>
#include <GameObject.h>

class Component : Object
{
public:
	Component(GameObject* owner) : _GameObject(owner) {}
	virtual ~Component() {}

	GameObject* GetGameObject() { return _GameObject; }
	virtual void OwnerActiveChange(bool newActive) {}

protected:
	GameObject* _GameObject;
};
