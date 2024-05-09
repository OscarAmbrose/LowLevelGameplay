#include "AnimationManager.h"
#include "GameObject.h"

bool AnimationManager::findSpriteRenderer()
{
	spriteRenderer = nullptr;
	if (spriteRenderer = _GameObject->GetComponent<SpriteRenderer>())
	{
		return true;
	}
	else
	{
		return false;
	}
}

SpriteRenderer* AnimationManager::returnSpriteRenderer()
{
	return spriteRenderer;
}

void AnimationManager::FixedUpdate(float deltaTime)
{
	
}
