#pragma once
#include <GameObject.h>
#include <vector>
#include <Transform.h>

GameObject::GameObject()
{
	SetActive(true);
	transform = AddComponent<Transform2D>();
}
