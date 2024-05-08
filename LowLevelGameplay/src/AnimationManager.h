#pragma once
#include <SpriteRenderer.h>
#include <stdexcept>
#include <vector>
#include <memory>
#include <Event.h>
#include "AnimationState.h"

class AnimationManager : public Component
{
public:
	AnimationManager(GameObject* owner) : Component(owner)
	{
		if (findSpriteRenderer() == false)
		{
			throw std::invalid_argument("Game Object contains no Sprite Renderer.");
		}
		testActiveAnimState = new AnimationState(this);
	};

	bool findSpriteRenderer();

	SpriteRenderer* returnSpriteRenderer();

	void FixedUpdate(float deltaTime);

protected:
	SpriteRenderer* spriteRenderer;
	std::vector<std::unique_ptr<AnimationState>> animationStates;
	AnimationState* testActiveAnimState;
};
