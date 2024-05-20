#include "Physics.h"

Physics::~Physics()
{
}

void Physics::RegisterCollider(Collider* col)
{
}

void Physics::DeregisterCollider(Collider* col)
{
}

void Physics::RegisterRigidBody(RigidBody* rb)
{
}

void Physics::CollectCollisions()
{
}

void Physics::DispatchCollisions()
{
}

bool CollisionInfo::operator==(const CollisionInfo& other)
{
	return false;
}

CollisionInfo CollisionInfo::Reverse()
{
	return CollisionInfo();
}
