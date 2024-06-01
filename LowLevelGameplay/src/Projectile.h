#pragma once
#include <GameObject.h>
#include <Vector2.h>

class RigidBody;

class Projectile : public GameObject
{
public:
	Projectile();
	~Projectile();

	void FixedUpdate(float deltaTime);

	void ProjectileCollision(CollisionInfo* col);

	void EnableProjectile(LLGP::Vector2f projectileDir, LLGP::Vector2f projectileLocation, float velocity, int bounceAmount);

	void DisableProjectile();

protected:
	void SetActive (bool newActive);

	LLGP::Vector2f m_Direction;

	int m_BounceAmount = 0;
};
