#pragma once
#include <Vector2.h>
#include <SFML/Graphics.hpp>

namespace SR
{
	class SpriteRenderer 
	{
		LLGP::Vector2<float> worldPosition;
		LLGP::Vector2<float> scale;
		sf::RectangleShape shape;

		SpriteRenderer(LLGP::Vector2<float> worldLocation, LLGP::Vector2<float> worldScale, sf::Texture& texture);

		void Update(float dT);

		void Start();
		void Deconstructor();
	};
}

