#include "RigidBody.h"
#include "GameObject.h"

void RigidBody::FixedUpdate(float deltaTime)
{
	LLGP::Vector2f solvedForce = SolveForces(deltaTime);
	AddVelocity(solvedForce);
	
	//Check if player is over max speed.
	if (GetVelocity().GetMagnitude() > GetMaxSpeed())
	{
		SetVelocity(GetVelocity().Normalise() * GetMaxSpeed());
	}
	if (GetVelocity().x < 0.5 && GetVelocity().x > -0.5)
	{
		SetVelocity(LLGP::Vector2f(0, GetVelocity().y));
	}
	if (GetVelocity().y < 0.5 && GetVelocity().y > -0.5)
	{
		SetVelocity(LLGP::Vector2f(GetVelocity().x, 0));
	}

	std::cout << GetVelocity().x << std::endl;

	LLGP::Vector2f oldPos = _GameObject->getTransform()->returnPosition();

	LLGP::Vector2f newPosition;

	newPosition = (GetVelocity()* deltaTime) + (_GameObject->getTransform()->returnPosition());

	LLGP::Vector2f distance = newPosition - oldPos;

	setDistanceTravelled(distance.GetMagnitude());

	_GameObject->getTransform()->setPosition(newPosition);
}

void RigidBody::addForce(LLGP::Vector2f force)
{
	AddNetForce(force);
}

LLGP::Vector2f RigidBody::SolveForces(float deltaTime)
{
	Vector2f velocityToAdd = LLGP::Vector2f::zero;

	if (GravityIsEnabled())
	{
		m_NetForce += GetGravityForce();
	}
	m_NetForce += CalculateFrictionForce(deltaTime);
	m_NetForce += CalculateDragForce(deltaTime);

	//std::cout << std::endl << "Delta Time: " << deltaTime << std::endl;

	//std::cout << "m_NetForce = " << m_NetForce.x << ", " << m_NetForce.y << std::endl;
	
	velocityToAdd = (m_NetForce / GetMass()) * deltaTime;

	//std::cout << "velocityToAdd = " << velocityToAdd.x << ", " << velocityToAdd.y << std::endl;

	m_NetForce = Vector2f::zero;

	return velocityToAdd;
}

LLGP::Vector2f RigidBody::CalculateFrictionForce(float deltaTime)
{
	//If friction is unneeded, return
	if (!IsGrounded() || GetVelocity().x == 0)
	{
		return LLGP::Vector2<float>::zero;
	}

	float returnForce = 0;

	returnForce = CalculateOpposingForce(deltaTime, GetVelocity().x, GetFriction());

	//Return friction in the X axis
	return LLGP::Vector2f(returnForce, 0);
}

float RigidBody::CalculateOpposingForce(float deltaTime, float velocityToOppose, float opposingForceStrength)
{
	float attemptedForce = 0;
	float returnForce = 0;

	// A = V/dT therefore:
	// F = V/dT * M
	float velocityForce = ((velocityToOppose / deltaTime) * GetMass());


	//Make sure the friction force is in the correct direction
	if (velocityForce > 0)
	{
		attemptedForce = -opposingForceStrength;
	}
	else if (velocityForce < 0)
	{
		attemptedForce = opposingForceStrength;
	}

	//Check that the friction force isn't greater than the velocities force.
	//if ((attemptedForce > 0 && velocityForce < attemptedForce && velocityForce > 0) || (attemptedForce < 0 && velocityForce > attemptedForce && velocityForce < 0))
	//{
	//	returnForce = -velocityForce;
	//}

	if ((velocityForce > 0 && velocityForce - attemptedForce < 0) || (velocityForce < 0 && velocityForce - attemptedForce > 0))
	{
		returnForce = -velocityForce;
	}
	else
	{
		returnForce = attemptedForce;
	}

	return returnForce;
}

LLGP::Vector2f RigidBody::CalculateDragForce(float deltaTime)
{
	//If Drag is unneeded, return.
	if (IsGrounded() || GetVelocity().GetSquareMagnitude() == 0)
	{
		return LLGP::Vector2f::zero;
	}
	LLGP::Vector2f DragForce = LLGP::Vector2f::zero;

	float returnForceX = CalculateOpposingForce(deltaTime, GetVelocity().x, GetDrag());
	float returnForceY = CalculateOpposingForce(deltaTime, GetVelocity().y, GetDrag());

	float test = m_Velocity.GetSquareMagnitude();

	DragForce *= (test * test);

	DragForce = LLGP::Vector2f(returnForceX, returnForceY);

	return DragForce;
}
