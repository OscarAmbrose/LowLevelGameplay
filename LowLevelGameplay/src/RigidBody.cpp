#include "RigidBody.h"

void RigidBody::FixedUpdate(float deltaTime)
{

}

void RigidBody::addForce(LLGP::Vector2f force)
{
	m_Velocity += force;
}
