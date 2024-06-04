#pragma once
#include <Collider.h>
#include <Vector2.h>

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* owner);

	~BoxCollider();

	void Start(float deltaTime);

	BoxCollider* SetUpCollider(LLGP::Vector2f boxSize, LLGP::Vector2f boxOffset);

	inline LLGP::Vector2f GetBoxSize() { return m_BoxSize; }
	void SetBoxSize(LLGP::Vector2f newBoxSize);

	inline LLGP::Vector2f GetBoxPosition() { return m_BoxPosition; }
	inline void SetBoxPosition(LLGP::Vector2f newBoxPosition) { m_BoxPosition = newBoxPosition; }

	BoxCollider* SetDebugEnabled(bool newDebug);

	BoxCollider* SetCollisionBoundToPlayer(bool newTied) { m_CollisionIsTiedToPlayer = newTied; this; }

	inline LLGP::Vector2f GetOffset() { return m_Offset; }
	inline void SetOffset(LLGP::Vector2f newOffset) { m_Offset = newOffset; }

	CollisionInfo* IsCollidingWith(Collider* other) override;
	CollisionInfo* IsCollidingWith(BoxCollider* other) override;

	LLGP::Vector2f GetBoxHalfExtents() { return (GetBoxSize() / 2); }

	void FixedUpdate(float deltaTime);
	
protected:
	LLGP::Vector2f m_BoxSize = LLGP::Vector2f(100,100);
	LLGP::Vector2f m_BoxPosition = LLGP::Vector2f(0.f,0.f);
	LLGP::Vector2f m_Offset = LLGP::Vector2f(0.f, 0.f);
	LLGP::Vector2f m_HalfBoxExtents = LLGP::Vector2f(100.f, 100.f);
	bool m_DebugEnabled = false;
	bool m_CollisionIsTiedToPlayer = true;
};
