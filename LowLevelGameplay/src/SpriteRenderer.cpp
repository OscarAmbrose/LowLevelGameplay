#include "SpriteRenderer.h"
#include <Transform.h>

void SpriteRenderer::setUV(Vector2i selectedSprite)
{
	Vector2i spritesInTexture = Vector2i(32, 16);
	rectangleSize = Vector2<float>(32, 64);
	Vector2i rectTexSize(shape.getTexture()->getSize());
	sf::IntRect rectTexUV((rectTexSize.x / spritesInTexture.x) * selectedSprite.x, (rectTexSize.y / spritesInTexture.y) * selectedSprite.y, rectTexSize.x / spritesInTexture.x, rectTexSize.y / spritesInTexture.y);
	shape.setTextureRect(rectTexUV);
}

void SpriteRenderer::setUV(Vector2i selectedSprite, Vector2i spriteSize)
{
	Vector2i spritesInTexture = Vector2i(32, 16);
	rectangleSize = Vector2<float>(spriteSize.x, spriteSize.y);
	Vector2i rectTexSize(shape.getTexture()->getSize());
	sf::IntRect rectTexUV((rectTexSize.x / spritesInTexture.x) * selectedSprite.x, (rectTexSize.y / spritesInTexture.y) * selectedSprite.y, spriteSize.x, spriteSize.y);
	shape.setTextureRect(rectTexUV);
}

sf::RectangleShape SpriteRenderer::returnShape()
{
	//LLGP::Vector2<float> rectSize = Vector2<float>(32, 64);
	shape.setSize(rectangleSize);
	shape.setOrigin(rectangleSize / 2);
	shape.setRotation(parentTransform->returnRotation());

	LLGP::Vector2f position = parentTransform->returnPosition() + offset;

	shape.setPosition(position);

	return shape;
}

void SpriteRenderer::renderShape(sf::RenderWindow* window)
{
	window->draw(returnShape());
}

//void SpriteRenderer::renderShape(float RenderNum)
//{
//	std::cout << "MOEW" << std::endl;
//}
