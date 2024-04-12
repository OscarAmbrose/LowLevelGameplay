#pragma once
#include <SFML/Graphics.hpp>
#include <Vector2.h>
#include<chrono>
#include<iostream>
#include<Player.h>
//#include<Component.h>

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

	
	//Component Testing
	/*Component test1Component = Component();
	testClass test2Component = testClass();
	testClass test3Component = testClass();
	testClass test4Component = testClass();
	testClass test5Component = testClass();
	Component* pointer1 = &test2Component;
	Component* pointer2 = &test3Component;
	Component* pointer3 = &test4Component;
	Component* pointer4 = &test5Component;
	test1Component.AddComponent(pointer1);
	test1Component.AddComponent(pointer2);
	test1Component.AddComponent(pointer3);
	test1Component.AddComponent(pointer4);

	test1Component.removeComponent(pointer3);

	test1Component.removeAllComponents();*/
	//End Component Testing

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
