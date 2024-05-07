#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

extern sf::Texture* renderTexture;

class GlobalTexture
{
public:
	GlobalTexture()
	{
		renderTexture = new sf::Texture();
		renderTexture->loadFromFile("Textures/JoustSpritesActual.png");
	}

	~GlobalTexture() {};
};
