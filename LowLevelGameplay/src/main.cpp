#pragma once
#include <SFML/Graphics.hpp>
#include <Vector2.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	shape.setScale(0.5f, 0.5f);

	float x = 0.1;
	bool c = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			shape.setFillColor(sf::Color::Red);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			shape.setFillColor(sf::Color::Green);
			//sf::Vector2f shapeTransform(shape.getTransform().transformPoint);
		}

		

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
