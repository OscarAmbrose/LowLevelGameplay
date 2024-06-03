#pragma once
#include <GameObject.h>
#include <Vector2.h>

class RigidBody;
class Timer;

class Projectile : public GameObject
{
public:
	Projectile();
	~Projectile();

	void FixedUpdate(float deltaTime);

	void ProjectileCollision(CollisionInfo* col);

	void LifeTimeEnded(int Successful);

	void EnableProjectile(LLGP::Vector2f projectileDir, LLGP::Vector2f projectileLocation, float velocity, int bounceAmount);

	void DisableProjectile();

protected:
	void SetActive (bool newActive);

	LLGP::Vector2f m_Direction;

	float m_ProjectileLifetime = 2.f;

	std::unique_ptr<Timer> m_CurrentTimer = std::make_unique<Timer>(m_ProjectileLifetime);


	int m_BounceAmount = 0;
};
