#pragma once
#include <UUID.h>
#include "Transform.h"

using namespace LLGP;

class Object
{
public:
	Object() : uuid() {}
	Object(const Object&) = default;

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;

	UUID uuid;

	inline bool operator==(const Object& rhs) { return (uint64_t)this->uuid == (uint64_t)rhs.uuid; }
	inline bool operator!=(const Object& rhs) { return !(*this == rhs); }
};
