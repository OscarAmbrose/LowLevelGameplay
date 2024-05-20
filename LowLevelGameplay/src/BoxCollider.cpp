#include "BoxCollider.h"
#include "GameObject.h"

BoxCollider::BoxCollider(GameObject* owner) : Collider(owner)
{

}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::setUpCollider(LLGP::Vector2i boxSize)
{
	SetBoxSize(boxSize);
}

CollisionInfo* BoxCollider::IsCollidingWith(Collider* other)
{
	return nullptr;
}

CollisionInfo* BoxCollider::IsCollidingWith(BoxCollider* other)
{
	return nullptr;
}
