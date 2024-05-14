#pragma once
#include <Component.h>

class RigidBody : public Component
{
public:
	RigidBody(GameObject* owner) : Component(owner)		
	{
		g_OnPhysicsUpdate.AddListener(this, std::bind(&RigidBody::FixedUpdate, this, std::placeholders::_1));
	};
	~RigidBody() {};

	void FixedUpdate(float deltaTime) override;

	void addForce(LLGP::Vector2f force);
	LLGP::Vector2f SolveForces(float deltaTime);
	LLGP::Vector2f CalculateFrictionForce(float deltaTime);

	float CalculateOpposingForce(float deltaTime, float velocityToOppose, float opposingForceStrength);

	LLGP::Vector2f CalculateDragForce(float deltaTime);

#pragma region Interact with Member Variables

	inline LLGP::Vector2f GetGravityForce() const { return m_GravityForce; }
	inline void SetGravity(LLGP::Vector2f newGravityForce) { m_GravityForce = newGravityForce; }

	inline float GetFriction() const { return m_FrictionForce; }
	inline void SetFriction(float newFriction) { m_FrictionForce = newFriction; }

	inline float GetDrag() const { return m_DragForce; }
	inline void SetDrag(float newDrag) { m_DragForce = newDrag; }

	inline float GetMass() const { return m_Mass; }
	inline void SetMass(float newMass) { m_Mass = newMass; }

	inline void SetAcceleration(LLGP::Vector2f newAccel) { m_Acceleration = newAccel; }
	inline LLGP::Vector2f GetAcceleration() const { return m_Acceleration; }

	inline void SetMaxSpeed(float newMax) { m_MaxSpeed = newMax; }
	inline float GetMaxSpeed() const { return m_MaxSpeed; }

	inline void OverrideNetForce(LLGP::Vector2f netForceOverride) { m_NetForce = netForceOverride; }
	inline LLGP::Vector2f GetNetForce() const { return m_NetForce; }

	inline LLGP::Vector2f AddVelocity(LLGP::Vector2f addedVelocity) { return (m_Velocity += addedVelocity); }
	inline LLGP::Vector2f GetVelocity() const { return m_Velocity; }

	inline bool IsGrounded() const { return m_isGrounded; }
	inline void SetIsGrounded(bool newGrounded) { m_isGrounded = newGrounded; }

	inline bool GravityIsEnabled() { return m_HasGravity; }
	inline void setGravityEnabled(bool newGrav) { m_HasGravity = newGrav; }

#pragma endregion

protected:
	inline LLGP::Vector2f AddNetForce(LLGP::Vector2f netForceToAdd) {return (m_NetForce += netForceToAdd); }

private:
	LLGP::Vector2f m_NetForce = LLGP::Vector2f(0.f, 0.f);//
	LLGP::Vector2f m_Velocity = LLGP::Vector2f(0.f, 0.f);
	float m_MaxSpeed = 100.f;//
	LLGP::Vector2f m_Acceleration = LLGP::Vector2f(0.f, 0.f);//
	float m_FrictionForce = 1.f;//
	float m_DragForce = 12.f;//
	LLGP::Vector2f m_GravityForce = LLGP::Vector2f(0, 9.81f);//
	float m_Mass = 1.f;//
	bool m_isGrounded = false;
	bool m_HasGravity = false;
};
