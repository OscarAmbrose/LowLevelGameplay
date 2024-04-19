#pragma once
#include <Object.h>
#include <Transform.h>
#include <iostream>
//#include <GameObject.h>

class GameObject;

class Component : virtual public Object
{
public:
	Component(GameObject* owner, Transform2D* pTransform) : _GameObject(owner) { parentTransform = pTransform; }
	//Component();
	virtual ~Component() {}

	void Start() { /*std::cout << "Start in Component" << std::endl;*/};
	void Update() { /*std::cout << "Update in Component" << std::endl;*/ };
	void FixedUpdate() { /*std::cout << "Fixed Update in Component" << std::endl;*/ };

	GameObject* GetGameObject() { return _GameObject; }
	virtual void OwnerActiveChange(bool newActive) {}

protected:
	GameObject* _GameObject;
	Transform2D* parentTransform = nullptr;
};
