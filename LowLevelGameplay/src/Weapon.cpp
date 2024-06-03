#include <Weapon.h>
#include <GlobalEvents.h>
#include <GameObject.h>
#include <Cursor.h>
#include <Timer.h>
#include <ObjectPool.h>
#include <Transform.h>

Weapon::Weapon(GameObject* owner) : Component(owner)
{
	m_CurrentAmmoCount = m_MaxAmmoCount;
	m_Timer = std::make_unique<Timer>(0.3f);
	m_Timer->TimerFinished.AddListener(this, std::bind(&Weapon::SetCanFire, this, std::placeholders::_1));
}

Weapon::~Weapon()
{

}

void Weapon::FixedUpdate(float deltaTime)
{
	m_AimDirection = _GameObject->GetComponent<Cursor>()->GetLookAtCursorDirection();
}

bool Weapon::Fire()
{
	if (!GetCanFire() || !HasAmmo()) { return false; }

	//Fire rate timer (I want this to be a different thread)
	m_Timer->StartTimer(1/m_FireRate);

	//Firing Logic (spawn bullet with direction and velocity.)
	LLGP::Vector2f fireLocation = _GameObject->GetTransform()->ReturnPosition() + (m_AimDirection * m_AimOffset);

	ObjectPooler::FindRemainingObject()->EnableProjectile(m_AimDirection, fireLocation, m_FireSpeed, m_ProjectileBounceAmount);

	SetAmmoCount(m_CurrentAmmoCount - 1);

	return true;
}
 
void Weapon::Reload()
{
	m_Timer->ClearAndInvalidateTimer();
	m_Reloading = true;
	m_Timer->StartTimer(m_ReloadTime);
	m_Timer->TimerFinished.AddListener(this, std::bind(&Weapon::RefillAmmo, this, std::placeholders::_1));
}

void Weapon::RefillAmmo(bool DoesFill)
{
	if (DoesFill)
	{
		m_CurrentAmmoCount = m_MaxAmmoCount;
	}
	m_Reloading = false;
	m_Timer->TimerFinished.RemoveListener(this, std::bind(&Weapon::RefillAmmo, this, std::placeholders::_1));
}

bool Weapon::HasAmmo()
{
	if (m_CurrentAmmoCount > 0) { return true; }
	if(!m_Reloading) { Reload(); }
	return false;
}

void Weapon::SetMaxAmmoCount(int newMaxAmmo, bool IsFilling)
{
	if (IsFilling) { m_CurrentAmmoCount = newMaxAmmo; }

	m_MaxAmmoCount = newMaxAmmo;
}

void Weapon::SetAmmoCount(int newAmmoCount)
{
	if (newAmmoCount > m_MaxAmmoCount) { m_CurrentAmmoCount = m_MaxAmmoCount; }
	else { m_CurrentAmmoCount = newAmmoCount; }
}
