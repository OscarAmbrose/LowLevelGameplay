#pragma once
#include <Component.h>
#include <SpriteRenderer.h>
#include <stdexcept>
#include <vector>

class GameObject;

class SpriteAnimator : public Component
{
public:
	SpriteAnimator(GameObject* owner) : Component(owner)
	{
		if (findSpriteRenderer() == false)
		{
			throw std::invalid_argument("Game Object contains no Sprite Renderer.");
		}
	};

	bool findSpriteRenderer();
protected:
	SpriteRenderer* spriteRenderer;
};
