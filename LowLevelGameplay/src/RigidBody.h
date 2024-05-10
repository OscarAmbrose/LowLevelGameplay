#pragma once
#include <Component.h>

class RigidBody : Component
{
public:
	RigidBody(GameObject* owner) : Component(owner) {};
	~RigidBody() {};

	void FixedUpdate(float deltaTime) override;

	void addForce(LLGP::Vector2f force);

private:
	float m_maxSpeed;
	LLGP::Vector2f m_acceleration;
	LLGP::Vector2f m_Velocity;
	float m_frictionForce = 5.f;
	float m_gravityForce = 9.81f;
	float m_netForce;
	float m_mass;
};
