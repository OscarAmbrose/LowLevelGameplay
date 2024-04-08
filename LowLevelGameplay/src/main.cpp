#pragma once
#include <SFML/Graphics.hpp>
#include <Vector2.h>
#include<chrono>
#include<iostream>
#include<Player.h>
#include<Component.h>

using namespace LLGP;

#define FIXEDFRAMERATE 0.016f

int main()
{
	Player* player = nullptr;

	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
	float deltaTime = 0.f;
	float timeSincePhysicsStep = 0.f;
	int numberOfFixedUpdates = 0;
	int numberOfUpdates = 0;

	sf::RenderWindow window(sf::VideoMode(1800, 1080), "SFML works!");
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Green);
	shape.setScale(1, 1);

	/*Vector2<float> rectSize = Vector2<float>::one * 100;
	Vector2<float> rectPos = Vector2<float>(450, 450);*/
	sf::Texture rectTex;

	

	Component testComponent = Component();
	testClass test2Component = testClass();
	
	testComponent.AddComponent(test2Component);

	if (!rectTex.loadFromFile("Textures/Test.png"))
	{
		std::cout << "Cannot load texture" << std::endl;
	}
	//Vector2i spritesInTex(1, 1);
	
	player = new Player(rectTex/* LLGP::Vector2f(0,0), rectSize*/);

	while (window.isOpen())
	{
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.f;
		lastTime = now;
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			shape.setFillColor(sf::Color::Red);
			rectPos += (Vector2<float>::left * 0.01f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			shape.setFillColor(sf::Color::White);
			rectPos += (Vector2<float>::right * 0.01f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			shape.setFillColor(sf::Color::Green);
			rectPos += (Vector2<float>::up * -0.01f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			shape.setFillColor(sf::Color::Blue);
			rectPos += (Vector2<float>::down * -0.01f);
		}*/

		timeSincePhysicsStep += deltaTime;
		while (timeSincePhysicsStep > FIXEDFRAMERATE) 
		{
			//step physics
			//collect collision info
			//dispatch collisions
			
			timeSincePhysicsStep -= FIXEDFRAMERATE;
		}

		window.clear();
		window.draw(shape);
		//window.draw(player->returnShape());
		window.draw(player->playerSprite);

		//List renderers

		window.display();
	}

	return 0;
}
