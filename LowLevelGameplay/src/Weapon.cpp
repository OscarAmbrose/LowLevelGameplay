#include <Weapon.h>
#include <GlobalEvents.h>
#include <GameObject.h>
#include <Cursor.h>
#include <Timer.h>
#include <ObjectPool.h>
#include <Transform.h>

Weapon::Weapon(GameObject* owner) : Component(owner)
{
	currentWeapon = new CurrentWeaponInfo();
	m_CurrentAmmoCount = currentWeapon->_MaxAmmo;
	m_FireDelayTimer = std::make_unique<Timer>(1.f/ 1.f);
	m_ReloadTimer = std::make_unique<Timer>(currentWeapon->_ReloadTime);
	m_FireDelayTimer->TimerFinished.AddListener(this, std::bind(&Weapon::SetCanFire, this, std::placeholders::_1));
	m_ReloadTimer->TimerFinished.AddListener(this, std::bind(&Weapon::RefillAmmo, this, std::placeholders::_1));
	g_OnStart.RemoveListener(this, std::bind(&Component::Start, this, std::placeholders::_1));
	currentWeapon->SetWeapon(4);
}

Weapon::~Weapon()
{
	g_OnStart.RemoveListener(this, std::bind(&Component::Start, this, std::placeholders::_1));
	g_OnUpdate.RemoveListener(this, std::bind(&Component::Update, this, std::placeholders::_1));
	delete currentWeapon;
}

void Weapon::FixedUpdate(float deltaTime)
{
	m_AimDirection = m_GameObject->GetComponent<Cursor>()->GetLookAtCursorDirection();
}

bool Weapon::Fire()
{
	if (!GetCanFire() || !HasAmmo()) { return false; }

	m_CanFire = false;
	//Fire rate timer (I want this to be a different thread)
	m_FireDelayTimer->StartTimer((1 / (currentWeapon->_FireRate)));

	//Firing Logic (spawn bullet with direction and velocity.)
	LLGP::Vector2f fireLocation = m_GameObject->GetTransform()->ReturnPosition() + (m_AimDirection * m_AimOffset);

	ObjectPooler::FindRemainingObject()->EnableProjectile(m_AimDirection, fireLocation, currentWeapon->_ProjectileSpeed, currentWeapon->_ProjectileBounceAmount);

	SetAmmoCount(m_CurrentAmmoCount - 1);

	return true;
}

void Weapon::Reload()
{
	if (m_CurrentAmmoCount == currentWeapon->_MaxAmmo) { return; }
	m_FireDelayTimer->ClearAndInvalidateTimer();
	m_ReloadTimer->StartTimer(currentWeapon->_ReloadTime);
	m_Reloading = true;
}

void Weapon::RefillAmmo(bool DoesFill)
{
	if (DoesFill)
	{
		m_CurrentAmmoCount = currentWeapon->_MaxAmmo;
	}
	m_Reloading = false;
	m_CanFire = true;
}

bool Weapon::HasAmmo()
{
	if (m_CurrentAmmoCount > 0) { return true; }
	if(!m_Reloading) { Reload(); }
	return false;
}

void Weapon::Update(float deltaTime)
{
	Component::Update(deltaTime);
	if (m_Firing)
	{
		Fire();
	}
}

void Weapon::SetMaxAmmoCount(int newMaxAmmo, bool IsFilling)
{
	if (IsFilling) { m_CurrentAmmoCount = newMaxAmmo; }

	currentWeapon->_MaxAmmo = newMaxAmmo;
}

void Weapon::SetAmmoCount(int newAmmoCount)
{
	if (newAmmoCount > currentWeapon->_MaxAmmo) { m_CurrentAmmoCount = currentWeapon->_MaxAmmo; }
	else { m_CurrentAmmoCount = newAmmoCount; }
}

void Weapon::CurrentWeaponInfo::SetWeapon(int weaponType)
{
	switch (weaponType)
	{
	case 1:
		_WeaponName = "Pistol";
		_RenderUV = LLGP::Vector2i(3, 5);
		_FireRate = 5.f;
		_ProjectileSpeed = 700.f;
		_ProjectileBounceAmount = 0;
		_ReloadTime = 0.7f;
		_MaxAmmo = 7;
		_Damage = 34.f;
		break;
	case 2:
		_WeaponName = "SMG";
		_RenderUV = LLGP::Vector2i(4, 5);
		_FireRate = 15.f;
		_ProjectileSpeed = 700.f;
		_ProjectileBounceAmount = 0;
		_ReloadTime = 1.6f;
		_MaxAmmo = 20;
		_Damage = 15.f;
		break;
	case 3:
		_WeaponName = "Shotgun";
		_RenderUV = LLGP::Vector2i(5, 5);
		_FireRate = 0.7f;
		_ProjectileSpeed = 700.f;
		_ProjectileBounceAmount = 0;
		_ReloadTime = 1.4f;
		_MaxAmmo = 6;
		_Damage = 14.f;
		break;

	case 4:
		_WeaponName = "Sniper";
		_RenderUV = LLGP::Vector2i(2, 5);
		_FireRate = 0.7f;
		_ProjectileSpeed = 1000.f;
		_ProjectileBounceAmount = 0;
		_ReloadTime = 1.1f;
		_MaxAmmo = 5;
		_Damage = 100.f;
		break;

	case 5:
		_WeaponName = "GoldenGun";
		_RenderUV = LLGP::Vector2i(1, 5);
		_FireRate = 1.f;
		_ProjectileSpeed = 1000.f;
		_ProjectileBounceAmount = 0;
		_ReloadTime = 1.3f;
		_MaxAmmo = 1;
		_Damage = 9999.f;
		break;

	default:
		_WeaponName = "Pistol";
		_RenderUV = LLGP::Vector2i(3, 5);
		_FireRate = 3.5f;
		_ProjectileSpeed = 600.f;
		_ProjectileBounceAmount = 0;
		_ReloadTime = 0.7f;
		_MaxAmmo = 7;
		_Damage = 34.f;
		break;
	}
}

bool Weapon::CurrentWeaponInfo::operator==(CurrentWeaponInfo* other)
{
	if (this->_WeaponName == other->_WeaponName)
	{
		return true;
	}
	return false;
}
