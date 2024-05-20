#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <GameObject.h>
#include <GlobalEvents.h>
#include <GameManager.h>
#include <AnimationManager.h>
#include <Physics.h>

#define FIXEDFRAMERATE (1.f/60.f)

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
	sf::RenderWindow window(sf::VideoMode(1800, 1080), "Not Actually Joust");
	
	std::unique_ptr<GlobalTexture> globalTextureTest = std::make_unique<GlobalTexture>();
	
	std::unique_ptr<GameManager> testGameManager = std::make_unique<GameManager>();

	std::cout << testGameManager->getGameObjectByName("Object") << std::endl;
	std::cout << testGameManager->getGameObjectByName("Test") << std::endl;

	//testGameManager->getGameObjectByName("Test")->GetComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(6, 10), LLGP::Vector2i(176, 18) );

	//Vector2<float> meow = Vector2<float>(15.f, 10.f);
	//int a = 10;
	//meow.x += a;
	//meow / a;
	//std::cout << (meow.x+=a) << std::endl;

	while (window.isOpen())
	{
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.f;
		lastTime = now;

		g_OnStart(0);

		#pragma region CloseWindow
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}


#pragma endregion

		//Input Handling
		numberOfUpdates++;
		g_OnUpdate(deltaTime);
		g_OnPollInputs(event);

		#pragma region Physics
		timeSincePhysicsStep += deltaTime;
		while (timeSincePhysicsStep > FIXEDFRAMERATE)
		{
			//step physics
			g_OnFixedUpdate(FIXEDFRAMERATE);
			//collect collision info
			g_OnCollisionUpdate(FIXEDFRAMERATE);
			//std::cout <<std::endl<< "Number of Fixed Updates: " << numberOfFixedUpdates << std::endl;
			g_OnPhysicsUpdate(FIXEDFRAMERATE);
			//dispatch collisions
			numberOfFixedUpdates++;
			timeSincePhysicsStep -= FIXEDFRAMERATE;
		}
		#pragma endregion
		//Update

		#pragma region Render
		window.clear();

		for (int i = 0; i < 5; i++)
		{
			g_OnRender(&window, i);
		}

		window.display();
#pragma endregion
	}

	return 0;
}
