#include "SpriteRenderer.h"
#include <Transform.h>
#include <GameObject.h>
#include <Event.h>


SpriteRenderer* SpriteRenderer::setUV(LLGP::Vector2i selectedSprite)
{
	rectangleSize = LLGP::Vector2<float>(32, 64);
	sf::IntRect rectTexUV((rectTexSize.x / spritesInTexture.x) * selectedSprite.x, (rectTexSize.y / spritesInTexture.y) * selectedSprite.y, rectTexSize.x / spritesInTexture.x, rectTexSize.y / spritesInTexture.y);
	shape.setTextureRect(rectTexUV);
	return this;
}

SpriteRenderer* SpriteRenderer::setUV(LLGP::Vector2i selectedSprite, LLGP::Vector2i spriteSize)
{
	rectangleSize = LLGP::Vector2<float>(spriteSize.x, spriteSize.y);
	sf::IntRect rectTexUV((rectTexSize.x / spritesInTexture.x) * selectedSprite.x, (rectTexSize.y / spritesInTexture.y) * selectedSprite.y, spriteSize.x, spriteSize.y);
	shape.setTextureRect(rectTexUV);
	return this;
}

sf::RectangleShape SpriteRenderer::returnShape()
{
	shape.setSize(rectangleSize);
	shape.setOrigin(rectangleSize / 2);
	shape.setRotation(_GameObject->GetTransform()->returnRotation());

	LLGP::Vector2f position = _GameObject->GetTransform()->returnPosition() + offset;

	shape.setPosition(position);

	return shape;
}

void SpriteRenderer::setFlipped(bool newFlipped)
{

	isFlipped = newFlipped;
	float x = _GameObject->GetTransform()->returnScale().x;
	float y = _GameObject->GetTransform()->returnScale().y;
	if (newFlipped)
	{
		shape.setScale(-x, x);
	}
	else
	{
		shape.setScale(x, x);
	}

}

void SpriteRenderer::renderShape(sf::RenderWindow* window, int renderLayer)
{
	if (renderLayer == getRenderLayer())
	{
		window->draw(returnShape());
	}
}

SpriteRenderer* SpriteRenderer::setOffSet(LLGP::Vector2f newOffset)
{
	offset = newOffset;
	return this;
}

SpriteRenderer* SpriteRenderer::setRenderLayer(int newRenderLayer)
{
	m_RenderLayer = newRenderLayer;
	return this;
}
