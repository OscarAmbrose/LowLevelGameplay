#pragma once
#include <memory>
#include <vector>
#include <Vector2.h>

class Collider;
class RigidBody;

struct CollisionInfo
{
	CollisionInfo() 
	{
		collider = nullptr;
		otherCollider = nullptr;
	}

	Collider* collider;
	Collider* otherCollider;
	bool otherIsRB = false;
	LLGP::Vector2f Location = LLGP::Vector2f(0,0);
	LLGP::Vector2f Normal = LLGP::Vector2f(0, 0);
	float Overlap = 0.f;
	LLGP::Vector2f Impulse = LLGP::Vector2f(0, 0);

	bool operator==(const CollisionInfo& other);

	CollisionInfo Reverse();
};

class Physics
{
public:
	//Force a static class
	Physics() = delete;
	//I dont think this is necesarry, but its habit:
	~Physics();

	//Remove a collider from the collider list
	static void RegisterCollider(Collider* col);
	static void DeregisterCollider(Collider* col);
	static void RegisterRigidBody(RigidBody* rb);
	static void CollectCollisions();
	static void DispatchCollisions();
protected:
	static std::vector<Collider*> _colliders;
	static std::vector<RigidBody*> _rigidBodies;
	static std::vector<CollisionInfo*> _collisions;
	static std::vector<CollisionInfo*> _oldCollisions;
};
