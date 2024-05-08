#pragma once
#include "AnimationState.h"
#include "AnimationManager.h"

AnimationState::AnimationState(AnimationManager* animManager)
{
	m_animationManager = animManager;
	std::vector<LLGP::Vector2i> defaultAnimation;
	for (int i = 0; i < 4; i++)
	{
		LLGP::Vector2i animationPose = LLGP::Vector2i(i, 0);
		defaultAnimation.push_back(animationPose);
	}
	addAnimation(defaultAnimation);
	currentAnimPos = -1;
}

AnimationState::~AnimationState()
{

}

void AnimationState::addAnimation(std::vector<LLGP::Vector2i> animation)
{
	m_animationPositions = animation;
	m_animationPositions.push_back(LLGP::Vector2i(1024, 1024));
}

void AnimationState::updateRenderer(LLGP::Vector2i position)
{
	m_animationManager->returnSpriteRenderer()->setUV(position);
}

void AnimationState::updateRenderer(LLGP::Vector2i position, LLGP::Vector2i size)
{
	m_animationManager->returnSpriteRenderer()->setUV(position, size);
}

