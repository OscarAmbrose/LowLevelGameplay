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
		std::vector<LLGP::Vector2i> animArgu;
		for (int i = 0; i < 4; i++)
		{
			animArgu.push_back(Vector2i(i, 0));
		}
		//Testing
		AnimationState* testAnimState = new AnimationState(this);
		Animation* tempAnim = testAnimState->AddAnimation();
		tempAnim ->setName((std::string)"Bird_Walk");
		tempAnim->addAnimation(4, LLGP::Vector2i(0, 2), LLGP::Vector2i(1, 2), LLGP::Vector2i(2, 2), LLGP::Vector2i(3, 2));
		testAnimState->setActive(true);
	};

	bool findSpriteRenderer();

	SpriteRenderer* returnSpriteRenderer();

	void FixedUpdate(float deltaTime);

protected:
	SpriteRenderer* spriteRenderer;
	std::vector<std::unique_ptr<AnimationState>> animationStates;

	Animation* testAnim;
};
