#pragma once
#include <GameObject.h>
#include <vector>
#include <Transform.h>

GameObject::GameObject()
{
	transform.get()->setPosition(LLGP::Vector2f(0.f,0.f));
	SetActive(true);
}
