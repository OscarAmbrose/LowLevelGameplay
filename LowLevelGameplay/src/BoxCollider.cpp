#include "BoxCollider.h"
#include "GameObject.h"

BoxCollider::BoxCollider(GameObject* owner) : Component(owner)
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

void BoxCollider::Update(float deltaTime)
{	
	Component::Update(deltaTime);
	SetBoxPosition(_GameObject->getTransform()->returnPosition() + GetOffset());
}
