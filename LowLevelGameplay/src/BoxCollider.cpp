#include "BoxCollider.h"
#include "GameObject.h"
#include <Transform.h>
#include <Physics.h>
#include <DebugBox.h>
#include <GlobalEvents.h>
#include <bitset>

BoxCollider::BoxCollider(GameObject* owner) : Collider(owner)
{
	//SetUpCollider(LLGP::Vector2f(26, 38), LLGP::Vector2f(-7, -9));
	SetCollisionLayer(0b00000000);
	SetCollisionMask(0b00000000);
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Start(float deltaTime)
{
	if (m_DebugEnabled)
	{
		_GameObject->AddComponent<DebugBox>()->SetUpDebugBox();
	}
}


BoxCollider* BoxCollider::SetUpCollider(LLGP::Vector2f boxSize, LLGP::Vector2f boxOffset)
{
	m_Offset = boxOffset;
	m_BoxPosition = _GameObject->GetTransform()->ReturnPosition() + GetOffset();
	m_BoxSize = boxSize;
	m_HalfBoxExtents = LLGP::Vector2f(GetBoxSize().x/2, GetBoxSize().y/2) * _GameObject->GetTransform()->returnScale();
	return this;
}

void BoxCollider::SetBoxSize(LLGP::Vector2f newBoxSize)
{
	m_BoxSize = newBoxSize;
	m_HalfBoxExtents = LLGP::Vector2f(GetBoxSize().x / 2, GetBoxSize().y / 2) * _GameObject->GetTransform()->returnScale();
}

BoxCollider* BoxCollider::SetDebugEnabled(bool newDebug)
{
	m_DebugEnabled = newDebug;
	return this;
}

CollisionInfo* BoxCollider::IsCollidingWith(Collider* other)
{
	return IsCollidingWith((BoxCollider*)other);
}

CollisionInfo* BoxCollider::IsCollidingWith(BoxCollider* other)
{
	return Physics::Collision_AABBAABB(this, other);
}

void BoxCollider::Update(float deltaTime)
{	
	Component::Update(deltaTime);
	SetBoxPosition(_GameObject->GetTransform()->ReturnPosition() + GetOffset());
	
}
