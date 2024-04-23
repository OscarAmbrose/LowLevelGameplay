#pragma once
#include <Object.h>
//#include <Transform.h>
#include <iostream>
//#include <GameObject.h>

//class Transform2D;
class GameObject;

class Component : public Object
{
protected:
	GameObject* _GameObject;
	Transform2D* parentTransform = nullptr;
public:
	Component(GameObject* owner, Transform2D* pTransform) : _GameObject(owner) { parentTransform = pTransform; }
	//Component();
	virtual ~Component() {}

	void Start() override { /*std::cout << "Start in Component" << std::endl;*/};
	void Update() override { /*std::cout << "Update in Component" << std::endl;*/ };
	void FixedUpdate() override { /*std::cout << "Fixed Update in Component" << std::endl;*/ };

	GameObject* GetGameObject() { return _GameObject; }
	virtual void OwnerActiveChange(bool newActive) {}


};
