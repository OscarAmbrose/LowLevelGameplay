#pragma once
#include <Vector2.h>
#include <vector>

class Collider;
class BoxCollider;
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

	bool operator==(const CollisionInfo& other);

	CollisionInfo Reverse();
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

	static CollisionInfo* Collision_AABBAABB(BoxCollider* lhs, BoxCollider* rhs);

private:
	static std::vector<RigidBody*> _rigidBodies;
	static std::vector<Collider*> _colliders;
	static std::vector<CollisionInfo*> _collisions;
	static std::vector<CollisionInfo*> _oldCollisions;
};
