#include "Projectile.h"
#include <RigidBody.h>
#include <SpriteRenderer.h>
#include <BoxCollider.h>
#include <DebugBox.h>
#include <Transform.h>
#include <GlobalEvents.h>
#include <ScreenWrapper.h>
#include <Physics.h>

Projectile::Projectile()
{
	SetActive(false);
	AddComponent<RigidBody>()->setGravityEnabled(false)->SetMaxSpeed(1500.f)->SetDrag(0.f);
	AddComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(10, 2))->setRenderLayer(0);

	AddComponent<ScreenWrapper>();

	AddComponent<BoxCollider>()->SetUpCollider(LLGP::Vector2f(8, 8), LLGP::Vector2f(0, 0))->SetIsTrigger(true)->SetCollisionMask(0b11110111)->SetCollisionLayer(0b00001000);
	AddComponent<DebugBox>()->SetUpDebugBox();
}

Projectile::~Projectile()
{
	onCollisionEnter.RemoveListener(this, std::bind(&Projectile::ProjectileCollision, this, std::placeholders::_1));

	g_OnFixedUpdate.RemoveListener(this, std::bind(&Projectile::FixedUpdate, this, std::placeholders::_1));
}

void Projectile::FixedUpdate(float deltaTime)
{
}

void Projectile::ProjectileCollision(CollisionInfo* col)
{
	if (!col->otherCollider->GetGameObject()->GetActive() || !GetActive()) { return; }

	if (col->otherCollider->GetGameObject()->CompareTag("Player")) 
	{ 
		std::cout << "Hit Player" << std::endl;
		DisableProjectile();
		m_BounceAmount = 0;
		return;
	}
	//Damage other collider
	m_BounceAmount--;
	if (m_BounceAmount < 0) { DisableProjectile(); }
}

void Projectile::EnableProjectile(LLGP::Vector2f projectileDir, float velocity, int bounceAmount)
{
	GetComponent<RigidBody>()->SetVelocity(projectileDir * velocity);
	m_BounceAmount = bounceAmount;
	SetActive(true);
}

void Projectile::DisableProjectile()
{
	GetComponent<RigidBody>()->SetVelocity(LLGP::Vector2f::zero);
	SetActive(false);
}



void Projectile::SetActive(bool newActive)
{
	m_Active = newActive;
	if (m_Active)
	{
		onCollisionEnter.AddListener(this, std::bind(&Projectile::ProjectileCollision, this, std::placeholders::_1));
		g_OnFixedUpdate.AddListener(this, std::bind(&Projectile::FixedUpdate, this, std::placeholders::_1));
	}
	else
	{
		g_OnFixedUpdate.RemoveListener(this, std::bind(&Projectile::FixedUpdate, this, std::placeholders::_1));
		onCollisionEnter.RemoveListener(this, std::bind(&Projectile::ProjectileCollision, this, std::placeholders::_1));
	}
}