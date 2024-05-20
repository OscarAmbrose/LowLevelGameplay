#pragma once
#include <Component.h>

class Physics;
class BoxCollider;
struct CollisionInfo;

class Collider : public Component
{
public:
	Collider(GameObject* owner);
	~Collider();

	virtual CollisionInfo* IsCollidingWith(Collider* other) { return nullptr;  };
	virtual CollisionInfo* IsCollidingWith(BoxCollider* other) { return nullptr; };
};
