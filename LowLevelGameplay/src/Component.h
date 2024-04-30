#pragma once
#include <Object.h>
//#include <Transform.h>
#include <iostream>
//#include <GameObject.h>
//#include <GlobalEvents.h> 

//class Transform2D;
class GameObject;

class Component : public Object
{
protected:
	GameObject* _GameObject;
	Transform2D* parentTransform = nullptr;
public:
	Component(GameObject* owner);
	virtual ~Component();

	void Start() { };
	void Update(float deltaTime);
	void FixedUpdate() {};

	GameObject* GetGameObject() { return _GameObject; }
	virtual void OwnerActiveChange(bool newActive) {}
};
