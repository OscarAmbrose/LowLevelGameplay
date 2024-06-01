#pragma once
#include <Component.h>
#include <Vector2.h>

class Weapon : public Component
{
public:
	Weapon(GameObject* owner);
	~Weapon();

	void FixedUpdate(float deltaTime);

	bool Fire();

	inline bool GetCanFire() const { return m_CanFire; }
	inline void SetCanFire(bool newCanFire) { m_CanFire = newCanFire; }

	bool HasAmmo() const { return (m_CurrentAmmoCount > 0); }

	void SetMaxAmmoCount(int newMaxAmmo, bool IsFilling);

	void SetAmmoCount(int newAmmoCount);

	inline void SetAimDirection(LLGP::Vector2f newDirection) { m_AimDirection = newDirection; }
	LLGP::Vector2f GetAimDirection() const { return m_AimDirection; }

protected:
	LLGP::Vector2i m_WeaponUV = LLGP::Vector2i(10,3);
	float m_FireRate = 1.f;
	bool m_CanFire = true;
	float m_FireSpeed = 100.f;

	LLGP::Vector2f m_AimDirection = LLGP::Vector2f::zero;

	int m_MaxAmmoCount = 5;
	int m_CurrentAmmoCount;
};
