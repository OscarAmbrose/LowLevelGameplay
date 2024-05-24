#include "ScreenWrapper.h"
#include <GameObject.h>
#include <Transform.h>
#include <BoxCollider.h>
#include <JoustCharacter.h>

ScreenWrapper::ScreenWrapper(GameObject* owner) : Component (owner)
{
	if (boxCollider = _GameObject->GetComponent<BoxCollider>())
	{
		minimumScreenBounds -= boxCollider->GetBoxHalfExtents().x;
		maximumScreenBounds += boxCollider->GetBoxHalfExtents().x;
	}
	else
	{
		minimumScreenBounds -= 50.f;
		maximumScreenBounds += 50.f;
	}
}

ScreenWrapper::~ScreenWrapper()
{
}

void ScreenWrapper::FixedUpdate(float deltaTime)
{
	float PositionX = _GameObject->GetTransform()->returnPosition().x;
	float PositionY = _GameObject->GetTransform()->returnPosition().y;

	float newPositionX = 0;

	if (PositionY > maximumScreenBoundsY)
	{
		static_cast<Character*>(_GameObject)->KillChar();
	}

	if (PositionX < minimumScreenBounds)
	{
		newPositionX = maximumScreenBounds;
	}
	else if (PositionX > maximumScreenBounds)
	{
		newPositionX = minimumScreenBounds;
	}
	else
	{
		newPositionX = PositionX;
	}

	if (newPositionX != PositionX)
	{
		_GameObject->GetTransform()->setPosition(LLGP::Vector2f(newPositionX, PositionY));
	}
}
