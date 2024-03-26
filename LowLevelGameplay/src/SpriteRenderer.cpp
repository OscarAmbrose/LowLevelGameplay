#include "SpriteRenderer.h"

SR::SpriteRenderer::SpriteRenderer(LLGP::Vector2<float> worldLocation, LLGP::Vector2<float> worldScale, sf::Texture& texture)
{
	shape.setTexture(&texture);
	shape.setOrigin(worldScale / 2);
	shape.setPosition(worldLocation);
}

void SR::SpriteRenderer::Update(float dT)
{

}

void SR::SpriteRenderer::Start()
{
	sf::RectangleShape shape(LLGP::Vector2<float>(75,75));

}

SR::SpriteRenderer::~SpriteRenderer()
{
	
}

