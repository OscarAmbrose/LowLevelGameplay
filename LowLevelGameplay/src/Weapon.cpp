#include <Weapon.h>
#include <GlobalEvents.h>
#include <GameObject.h>
#include <Cursor.h>

Weapon::Weapon(GameObject* owner) : Component(owner)
{
	m_CurrentAmmoCount = m_MaxAmmoCount;
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
	if (!GetCanFire()) { return false; }

	//Firing Logic (spawn bullet with direction and velocity.


	SetAmmoCount(m_CurrentAmmoCount - 1);

	return true;
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
