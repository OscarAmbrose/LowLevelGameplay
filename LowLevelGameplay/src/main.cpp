#pragma once
#include <SFML/Graphics.hpp>
#include <Vector2.h>
#include <chrono>
#include <memory>
#include <iostream>
#include <SpriteRenderer.h>
#include <GameObject.h>
#include <Component.h>
#include <GlobalEvents.h>
#include <DispatcherTest1.h>
#include <ListenerTest.h>
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

	std::unique_ptr<GameObject> testGameObject = std::make_unique<GameObject>();
	testGameObject->AddComponent<SpriteRenderer>();
	Object* object = testGameObject.get();
	//object->Start();

	Object* srObj1 = testGameObject.get()->GetComponent<SpriteRenderer>();
	//srObj1->Start();

	//Event Dispatcher Testing (Working)
	std::unique_ptr<DispatcherTest> dispatcher = std::make_unique<DispatcherTest>();
	std::unique_ptr<ListenerTest> listener = std::make_unique<ListenerTest>(dispatcher.get());

	dispatcher->BroadcastOnMeowEvent(10);


	while (window.isOpen())
	{
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.f;
		lastTime = now;

		#pragma region CloseWindow
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
#pragma endregion

		//Input Handling

		#pragma region Physics
		timeSincePhysicsStep += deltaTime;
		while (timeSincePhysicsStep > FIXEDFRAMERATE)
		{
			//step physics
			//collect collision info
			//dispatch collisions
			timeSincePhysicsStep -= FIXEDFRAMERATE;
		}
		#pragma endregion

		//Update
		g_OnUpdate(deltaTime);

		#pragma region Render
		window.clear();

		window.draw(testGameObject.get()->GetComponent<SpriteRenderer>()->returnShape());

		window.display();
#pragma endregion
	}

	return 0;
}
