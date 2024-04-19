#include "Player.h"
#include <iostream>

Player::Player(sf::Texture& texture/*, LLGP::Vector2<float> worldLocation, LLGP::Vector2<float> worldScale*/)
{
	/*playerTexture = texture;
	worldPosition = worldLocation;
	scale = worldScale;*/

	//playerSprite.setScale(scale);
	//playerSprite.setPosition(worldPosition);
	//std::cout << worldPosition.x << worldPosition.y << std::endl;
	//playerSprite.setTexture(playerTexture);
	//std::cout << "PlayerCreated" << std::endl;
	
	LLGP::Vector2<float> rectSize = LLGP::Vector2<float>::one * 5;

	playerSprite.setScale(rectSize);
	playerSprite.setTexture(texture);
	playerSprite.setPosition(LLGP::Vector2(450, 450));
}

void Player::Update(float dT)
{

}

sf::Sprite Player::returnShape()
{
	//std::cout << "ReturnShape" << std::endl;
	return playerSprite;
}

//09-01-29
//23328365
//Max Bretherton
