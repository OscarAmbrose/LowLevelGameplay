#pragma once
#include <Object.h>
#include <GameObject.h>
#include <Component.h>
#include <Transform.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <GameObject.h>
#include <GlobalEvents.h>
#include <GameManager.h>
#include <AnimationManager.h>
#include <Physics.h>
#include <WindowManager.h>
#include <ObjectPool.h>
#include <Projectile.h>
#include <cstdlib>
#include <ctime>

#define FIXEDFRAMERATE (1.f/60.f)

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "GradEx 2024 ~ Oscar Ambrose", sf::Style::Fullscreen);

	WindowManager::SetNewWindow(&window);

	std::unique_ptr<GlobalTexture> globalTextureTest = std::make_unique<GlobalTexture>();
	
	std::unique_ptr <GameManager> gameManager = std::make_unique <GameManager>();

	ObjectPooler::InitialisePool();

	srand(static_cast<unsigned int>(time(0)));

	//Update Stuff
	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
	float deltaTime = 0.f;
	float timeSincePhysicsStep = 0.f;
	int numberOfFixedUpdates = 0;
	int numberOfUpdates = 0;
	//Update Stuff
	bool paused = false;
	

	//Creates the window
	
	
	
	while (window.isOpen())
	{

		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.f;
		lastTime = now;



		#pragma region CloseWindow
		sf::Event event;
		while (window.pollEvent(event))
		{
			//std::cout << "Event polled: " << event.type << std::endl;

			if (event.type == sf::Event::Closed)
			{
				window.close();
				continue;
			}

			if (event.type == sf::Event::LostFocus)
			{
				paused = true;
				continue;
			}
			if (event.type == sf::Event::GainedFocus)
			{
				paused = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				continue;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (numberOfFixedUpdates > 10))
			{
				for (int i = 0; i < 15; i++)
				{
					float DirectionX = -1 + 2 * ((float)rand() / RAND_MAX);
					float DirectionY = -1 + 2 * ((float)rand() / RAND_MAX);
					LLGP::Vector2f direction = LLGP::Vector2f(DirectionX, DirectionY).Normalised();
					ObjectPooler::FindRemainingObject()->EnableProjectile(direction, LLGP::Vector2f(450, 450), 750.f, 2);
					std::cout << ObjectPooler::GetRemainingObjects() << std::endl;
				}
				numberOfFixedUpdates = 0;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
			{
				ObjectPooler::DebugDisableAllPoolObjects();
			}
			
			g_OnPollInputs(event);
		}

		if (paused)
		{
			deltaTime = 0.f;
			continue;
		}

		g_OnStart(0);
#pragma endregion

		//Input Handling
		numberOfUpdates++;
		

		#pragma region Physics
		timeSincePhysicsStep += deltaTime;
		while (timeSincePhysicsStep > FIXEDFRAMERATE)
		{
			g_OnFixedUpdate(FIXEDFRAMERATE); 
			//step physics
			//collect collision info
			g_OnPhysicsUpdate(FIXEDFRAMERATE);

			Physics::CollectCollisions();
			
			//dispatch collisions
			Physics::DispatchCollisions();
			numberOfFixedUpdates++;
			timeSincePhysicsStep -= FIXEDFRAMERATE;
		}
		#pragma endregion
		//Update

		g_OnUpdate(deltaTime);
		#pragma region Render
		window.clear();

		//I should change this to a Bit shift and bit compare version, I think that'd be more efficient?
		for (int i = 0; i < 5; i++)
		{
			g_OnRender(&window, i);
		}

		window.display();
#pragma endregion
	}

	return 0;
}
