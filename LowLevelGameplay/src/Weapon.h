#pragma once
#include <Component.h>
#include <Vector2.h>

class Timer;

class Weapon : public Component
{
public:

	struct CurrentWeaponInfo
	{
		CurrentWeaponInfo() {};

		//Weapon 1 = Pistol, Weapon 2 = SMG, Weapon 3 = Shotgun, Weapon 4 = Sniper, Weapon 5 = GoldenGun
		void SetWeapon(int weaponType);

		std::string _WeaponName = "DefaultWeapon";
		LLGP::Vector2i _RenderUV = LLGP::Vector2i(2, 5);
		float _FireRate = 10.f;
		float _ProjectileSpeed = 800.f;
		int _ProjectileBounceAmount = 0;
		float _ReloadTime = 1.2f;
		int _MaxAmmo = 15;
		float _Damage = 34.f;

		bool operator==(CurrentWeaponInfo* other);
	};


	Weapon(GameObject* owner);
	~Weapon();

	void FixedUpdate(float deltaTime);

	bool Fire();

	void SetFiring(bool isFiring) { m_Firing = isFiring; }

	inline bool GetCanFire() const { return m_CanFire; }
	inline void SetCanFire(bool newCanFire) { m_CanFire = newCanFire; }

	void Reload();

	void RefillAmmo(bool DoesFill);

	bool HasAmmo();

	void Update(float deltaTime);

	void SetMaxAmmoCount(int newMaxAmmo, bool IsFilling);

	void SetAmmoCount(int newAmmoCount);

	inline void SetAimDirection(LLGP::Vector2f newDirection) { m_AimDirection = newDirection; }
	LLGP::Vector2f GetAimDirection() const { return m_AimDirection; }

protected:
	bool m_CanFire = true;

	bool m_Reloading = false;

	bool m_Firing = false;

	CurrentWeaponInfo* currentWeapon;

	LLGP::Vector2f m_AimDirection = LLGP::Vector2f::zero;
	float m_AimOffset = 50.f;

	std::unique_ptr<Timer> m_FireDelayTimer;
	std::unique_ptr<Timer> m_ReloadTimer;

	int m_CurrentAmmoCount;
};
