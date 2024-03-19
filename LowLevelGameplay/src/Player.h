#pragma once
#include <Vector2.h>
#include <SFML/Graphics.hpp>

class Player {
public:

	Player(sf::Texture texture/*, LLGP::Vector2<float> worldLocation, LLGP::Vector2<float> worldScale*/);

	void Update(float dT);

	sf::Sprite returnShape();

	//sf::Texture playerTexture;

	LLGP::Vector2<float> worldPosition;
	LLGP::Vector2<float> scale;
	sf::Sprite playerSprite;
	//sf::Texture playerTexture;
};
