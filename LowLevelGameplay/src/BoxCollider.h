#pragma once
#include <Collider.h>

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* owner);

	~BoxCollider();

	void setUpCollider(LLGP::Vector2i boxSize);

	CollisionInfo* IsCollidingWith(Collider* other) override;
	CollisionInfo* IsCollidingWith(BoxCollider* other) override;

	inline LLGP::Vector2i GetBoxSize() { return m_BoxSize; }
	inline void SetBoxSize(LLGP::Vector2i newBoxSize) { m_BoxSize = newBoxSize; }
protected:
	LLGP::Vector2i m_BoxSize = LLGP::Vector2i(0,0);
	LLGP::Vector2f m_BoxPosition = LLGP::Vector2f(0.f,0.f);

private:


};
