#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

extern std::shared_ptr<sf::Texture> renderTexture;

class GlobalTexture
{
public:
	GlobalTexture()
	{
		renderTexture = std::make_shared<sf::Texture>();
		renderTexture.get()->loadFromFile("Textures/JoustSpritesActual.png");
	}

	~GlobalTexture() {};
};
