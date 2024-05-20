#include "Collider.h"
#include "Physics.h"

Collider::Collider(GameObject* owner) : Component(owner)
{
	Physics::ReigsterColldier(this);
}

Collider::~Collider()
{
	Physics::DereigsterColldier(this);
}

