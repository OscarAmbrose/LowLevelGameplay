#include "SpriteRenderer.h"
#include <Transform.h>
#include <GameObject.h>
#include <Event.h>


SpriteRenderer* SpriteRenderer::setUV(LLGP::Vector2i selectedSprite)
{
	m_RectangleSize = LLGP::Vector2<float>(32, 64);
	sf::IntRect rectTexUV((rectTexSize.x / spritesInTexture.x) * selectedSprite.x, (rectTexSize.y / spritesInTexture.y) * selectedSprite.y, rectTexSize.x / spritesInTexture.x, rectTexSize.y / spritesInTexture.y);
	m_Shape.setTextureRect(rectTexUV);
	m_Shape.setSize(m_RectangleSize);
	m_Shape.setOrigin(m_RectangleSize / 2);

	return this;
}

SpriteRenderer* SpriteRenderer::setUV(LLGP::Vector2i selectedSprite, LLGP::Vector2i spriteSize)
{
	m_RectangleSize = LLGP::Vector2<float>(spriteSize.x, spriteSize.y);
	sf::IntRect rectTexUV((rectTexSize.x / spritesInTexture.x) * selectedSprite.x, (rectTexSize.y / spritesInTexture.y) * selectedSprite.y, spriteSize.x, spriteSize.y);
	m_Shape.setTextureRect(rectTexUV);
	m_Shape.setSize(m_RectangleSize);
	m_Shape.setOrigin(m_RectangleSize / 2);

	return this;
}

sf::RectangleShape SpriteRenderer::returnShape()
{
	m_Shape.setRotation(_GameObject->GetTransform()->returnRotation());

	LLGP::Vector2f position = _GameObject->GetTransform()->ReturnPosition() + offset;

	m_Shape.setPosition(position);

	return m_Shape;
}

void SpriteRenderer::setFlipped(bool newFlipped)
{

	isFlipped = newFlipped;
	float x = _GameObject->GetTransform()->returnScale().x;
	float y = _GameObject->GetTransform()->returnScale().y;
	if (newFlipped)
	{
		m_Shape.setScale(-x, x);
	}
	else
	{
		m_Shape.setScale(x, x);
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
