#pragma once
#include <Vector2.h>
#include <vector>
#include "Collider.h"
#include "BoxCollider.h"

class RigidBody;

struct CollisionInfo
{
	Collider* collider;
	Collider* otherCollider;
	bool otherIsRB;
	LLGP::Vector2f Location;
	LLGP::Vector2f Normal;
	float Overlap;
	LLGP::Vector2f Impulse;

	bool operator==(CollisionInfo* other);

};

class Physics
{
public:
	Physics() = delete;
	static void ReigsterColldier(Collider* col);
	static void DereigsterColldier(Collider* col);
	static void ReigsterRigidBody(RigidBody* rb);
	static void DereigsterRigidBody(RigidBody* rb);
	static void CollectCollisions();
	static void DispatchCollisions();
	static CollisionInfo* ReverseCollision(CollisionInfo* in);

	static CollisionInfo* Collision_AABBAABB(BoxCollider* lhs, BoxCollider* rhs);

private:
	static std::vector<RigidBody*> _rigidBodies;
	static std::vector<Collider*> _colliders;
	static std::vector<CollisionInfo*> _collisions;
	static std::vector<CollisionInfo*> _reversedCollisions;
	static std::vector<CollisionInfo*> _oldCollisions;
};
