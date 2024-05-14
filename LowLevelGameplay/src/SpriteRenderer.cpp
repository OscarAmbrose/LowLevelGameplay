#include "SpriteRenderer.h"
#include <Transform.h>

void SpriteRenderer::setUV(Vector2i selectedSprite)
{
	rectangleSize = Vector2<float>(32, 64);
	sf::IntRect rectTexUV((rectTexSize.x / spritesInTexture.x) * selectedSprite.x, (rectTexSize.y / spritesInTexture.y) * selectedSprite.y, rectTexSize.x / spritesInTexture.x, rectTexSize.y / spritesInTexture.y);
	shape.setTextureRect(rectTexUV);
}

void SpriteRenderer::setUV(Vector2i selectedSprite, Vector2i spriteSize)
{
	rectangleSize = Vector2<float>(spriteSize.x, spriteSize.y);
	sf::IntRect rectTexUV((rectTexSize.x / spritesInTexture.x) * selectedSprite.x, (rectTexSize.y / spritesInTexture.y) * selectedSprite.y, spriteSize.x, spriteSize.y);
	shape.setTextureRect(rectTexUV);
}

sf::RectangleShape SpriteRenderer::returnShape()
{
	shape.setSize(rectangleSize);
	shape.setOrigin(rectangleSize / 2);
	shape.setRotation(parentTransform->returnRotation());

	LLGP::Vector2f position = parentTransform->returnPosition() + offset;

	shape.setPosition(position);

	return shape;
}

void SpriteRenderer::renderShape(sf::RenderWindow* window, int renderLayer)
{
	if (renderLayer == getRenderLayer())
	{
		window->draw(returnShape());
	}
}
