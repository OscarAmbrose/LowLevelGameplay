#include "BoxCollider.h"
#include "GameObject.h"

BoxCollider::BoxCollider(GameObject* owner) : Collider(owner)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::SetUpCollider(LLGP::Vector2i boxSize)
{
	m_BoxPosition = _GameObject->getTransform()->returnPosition() + GetOffset();
	m_BoxSize = boxSize;
	m_HalfBoxExtents = LLGP::Vector2f(GetBoxSize().x/2, GetBoxSize().y/2) * _GameObject->getTransform()->returnScale();
}

CollisionInfo* BoxCollider::IsCollidingWith(Collider* other)
{
	return nullptr;
}

CollisionInfo* BoxCollider::IsCollidingWith(BoxCollider* other)
{
	return nullptr;
}

void BoxCollider::Update(float deltaTime)
{	
	Component::Update(deltaTime);
	SetBoxPosition(_GameObject->getTransform()->returnPosition() + GetOffset());
}
