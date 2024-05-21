#pragma once
#include <Component.h>
#pragma message("-------------------------Inlcuding Component in " __FILE__)

class BoxCollider;
struct CollisionInfo;

class Collider : public Component
{
public:
	Collider(GameObject* owner);
	~Collider();

	virtual CollisionInfo* IsCollidingWith(Collider* other) { return nullptr; };
	virtual CollisionInfo* IsCollidingWith(BoxCollider* other) { return nullptr; };

	uint8_t GetCollisionLayer() { return m_CollisionLayer; }
	uint8_t GetCollisionMask() { return m_CollisionMask; }
	void SetCollisionLayer(uint8_t bitLayer) { m_CollisionLayer = bitLayer; }
	void SetCollisionMask(uint8_t bitLayer) { m_CollisionMask = bitLayer; }

protected:
	uint8_t m_CollisionLayer = 0xff;
	uint8_t m_CollisionMask = 0xff;

};
