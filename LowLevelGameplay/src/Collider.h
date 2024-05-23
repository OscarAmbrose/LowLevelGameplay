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

	// Collision Layer Key:
	// 0b0000000X = platforms (default layer), everything that does blocking collisions should be here.
	// 0b000000X0 = player (joust collisions layer)
	// 0b00000X00 = enemies (used to make enemies ignore eachother on the joust layer)
	// 0b0000X000 = enemy eggs?
	// 0b000X0000 = lava troll
	// 0b00X00000 = lava
	// 0b0X000000 = unassigned
	// 0bX0000000 = unassigned
	void SetCollisionLayer(uint8_t bitLayer) { m_CollisionLayer = bitLayer; }
	Collider* SetCollisionMask(uint8_t bitLayer) { m_CollisionMask = bitLayer; return this; }

protected:
	uint8_t m_CollisionLayer = 0x00;
	uint8_t m_CollisionMask = 0x00;

};
