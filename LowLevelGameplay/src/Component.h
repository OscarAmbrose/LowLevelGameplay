#pragma once
#include <Object.h>
#include <iostream>
#include <GlobalEvents.h>

class GameObject;

struct CollisionInfo;

class Component : public Object
{
protected:
	GameObject* _GameObject;
	bool Started = false;
public:
	Component(GameObject* owner);
	virtual ~Component();

	virtual void Start(float start);
	virtual void Update(float deltaTime);
	virtual void FixedUpdate(float deltaTime);

	GameObject* GetGameObject() { return _GameObject; }
	virtual void OwnerActiveChange(bool newActive) {}
	
protected:
	virtual void OnCollisionEnter(CollisionInfo* col) {}
	virtual void OnCollisionStay(CollisionInfo* col) {}
	virtual void OnCollisionExit(CollisionInfo* col) {}
};
