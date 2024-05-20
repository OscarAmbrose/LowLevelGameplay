#include "Collider.h"
#include "Physics.h"
#include "BoxCollider.h"

Collider::Collider(GameObject* owner) : Component(owner)
{
	Physics::ReigsterColldier(this);
}

Collider::~Collider()
{
	Physics::DereigsterColldier(this);
}

