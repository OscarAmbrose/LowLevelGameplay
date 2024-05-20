#include "Collider.h"
#include "GameObject.h"

Collider::Collider(GameObject* owner) : Component(owner)
{

}

Collider::~Collider()
{
	Physics::DeregisterCollider(this);
}
