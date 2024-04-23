#pragma once
#include <SFML/Graphics.hpp>
#include <Vector2.h>
#include <chrono>
#include <memory>
#include <iostream>
#include <SpriteRenderer.h>
#include <Player.h>
#include <GameObject.h>
#include <Component.h>
//#include <DispatcherTest1.h>
//#include <ListenerTest.h>
//#include <Transform.h>

using namespace LLGP;

#define FIXEDFRAMERATE 0.016f

int main()
{
	//Update Stuff
	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
	float deltaTime = 0.f;
	float timeSincePhysicsStep = 0.f;
	int numberOfFixedUpdates = 0;
	int numberOfUpdates = 0;
	//Update Stuff

	//Creates the window
	sf::RenderWindow window(sf::VideoMode(1800, 1080), "SFML works!");
	
	//Circle shape for testing
	//sf::CircleShape shape(10.f);
	//shape.setFillColor(sf::Color::Green);
	//shape.setScale(1, 1);

	
	sf::Texture rectTex;
	//Try to load textures
	if (!rectTex.loadFromFile("Textures/Test.png"))
	{
		std::cout << "Cannot load texture" << std::endl;
	}

	std::unique_ptr<GameObject> testGameObject = std::make_unique<GameObject>();
	testGameObject->AddComponent<SpriteRenderer>();
	Object* object = testGameObject.get();
	object->Start();

	Object* srObj = testGameObject.get()->GetComponent<SpriteRenderer>();
	srObj->Start();
	//testGameObject.get()->GetComponent<SpriteRenderer>()->SetTexture("Textures/Test.png");

	//delete(object);
	//delete(srObj);

	//Loading textures works

	//Player Creation Testing (WORKING)
	std::unique_ptr<Player> player = NULL;
	player = std::make_unique<Player>(rectTex);
	//End of Player Creation Testing (WORKING)


	//Event Dispatcher Testing (Working)
	//std::unique_ptr<DispatcherTest> dispatcher = std::make_unique<DispatcherTest>();
	//std::unique_ptr<ListenerTest> listener = std::make_unique<ListenerTest>(dispatcher.get());

	//dispatcher->BroadcastOnMeowEvent(10);
	//dispatcher->BroadcastOnMeowEvent(10);
	//End of Event Dispatcher Testing (Working)


	while (window.isOpen())
	{
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.f;
		lastTime = now;

		//object->Update();

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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				GameObject* test = testGameObject.get();
				test->getTransform()->setRotation(test->getTransform()->returnRotation() - 5);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				GameObject* test = testGameObject.get();
				test->getTransform()->setRotation(test->getTransform()->returnRotation() + 5);
			}
			object->FixedUpdate();

			timeSincePhysicsStep -= FIXEDFRAMERATE;
		}

		window.clear();
		//window.draw(shape);
		window.draw(player->returnShape());
		//window.draw(player->playerSprite);
		window.draw(testGameObject.get()->GetComponent<SpriteRenderer>()->returnShape());

		//List renderers

		window.display();
	}

	return 0;
}
