#include "RigidBody.h"

void RigidBody::FixedUpdate(float deltaTime)
{

}

void RigidBody::addForce(LLGP::Vector2f force)
{
	AddNetForce(force);
}



LLGP::Vector2f RigidBody::SolveForces()
{
	m_NetForce += m_GravityForce;
	
}

float RigidBody::CalculateMaximumFrictionForce()
{
	float attemptedForce = 0;
	float returnForce = 0;
	if (IsGrounded())
	{
		if (m_Velocity.x > 0)
		{
			attemptedForce = -GetFriction();
		}
		else if (m_Velocity.x < 0)
		{
			attemptedForce = GetFriction();
		}
	}
	else
	{
		if (m_Velocity.x > 0)
		{
			attemptedForce = -GetFriction();
		}
		else if (m_Velocity.x < 0)
		{
			attemptedForce = GetFriction();
		}
	}

	if ((attemptedForce > 0 && GetVelocity().x < attemptedForce && GetVelocity().x > 0) ||( attemptedForce < 0 && GetVelocity().x > attemptedForce && GetVelocity().x < 0))
	{
		returnForce = -GetVelocity().x;
	}
	else
	{
		returnForce = attemptedForce;
	}
}
