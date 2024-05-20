#pragma once
#include "Vector2.h"

class Collider;

struct CollisionInfo
{
	Collider* collider;
	Collider* otherCollider;
	LLGP::Vector2f Location;
	LLGP::Vector2f Normal;
	float Overlap;
	LLGP::Vector2f Impulse;
};
