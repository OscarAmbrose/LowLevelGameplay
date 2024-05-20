#pragma once
#include "Physics.h"
#include "Component.h"
class BoxCollider;
struct CollisionInfo;

class Collider : public Component
{
public:
	Collider(GameObject* owner);
	~Collider();

	virtual CollisionInfo* IsCollidingWith(Collider* other) = 0;
	virtual CollisionInfo* IsCollidingWith(BoxCollider* other) = 0;
};
