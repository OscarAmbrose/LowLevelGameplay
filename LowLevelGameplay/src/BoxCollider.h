#pragma once
#include <Component.h>
#include <Collider.h>

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* owner);

	~BoxCollider();

	void SetUpCollider(LLGP::Vector2i boxSize);

	inline LLGP::Vector2i GetBoxSize() { return m_BoxSize; }
	inline void SetBoxSize(LLGP::Vector2i newBoxSize) { m_BoxSize = newBoxSize; }

	inline LLGP::Vector2f GetBoxPosition() { return m_BoxPosition; }
	inline void SetBoxPosition(LLGP::Vector2f newBoxPosition) { m_BoxPosition = newBoxPosition; }

	inline LLGP::Vector2f GetOffset() { return m_Offset; }
	inline void SetOffset(LLGP::Vector2f newOffset) { m_Offset = newOffset; }

	CollisionInfo* IsCollidingWith(Collider* other) override;
	CollisionInfo* IsCollidingWith(BoxCollider* other) override;

	inline LLGP::Vector2f GetBoxHalfExtents() { return m_HalfBoxExtents; }

	void Update(float deltaTime);

protected:
	LLGP::Vector2i m_BoxSize = LLGP::Vector2i(0,0);
	LLGP::Vector2f m_BoxPosition = LLGP::Vector2f(0.f,0.f);
	LLGP::Vector2f m_Offset = LLGP::Vector2f(0.f, 0.f);
	LLGP::Vector2f m_HalfBoxExtents = LLGP::Vector2f(0.f, 0.f);
private:


};
