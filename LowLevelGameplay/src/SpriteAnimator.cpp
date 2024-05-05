#include "SpriteAnimator.h"
#include "GameObject.h"

bool SpriteAnimator::findSpriteRenderer()
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
