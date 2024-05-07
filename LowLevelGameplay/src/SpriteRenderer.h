#pragma once
#include <Vector2.h>
#include <SFML/Graphics.hpp>
#include <Component.h>
#include <memory>
#include <GlobalTexture.h>

//class Transform2D;
class GameObject;

class SpriteRenderer : public Component
{
public:

	SpriteRenderer(GameObject* owner) : Component(owner) 
	{ 
		//std::cout << parentTransform << std::endl;
		SetTexture("Textures/JoustSpritesActual.png");
	}

	~SpriteRenderer()
	{
		std::cout << "Meow" << std::endl;
	}
	
	void SetTexture(std::string filePath);

	void setUV(Vector2i selectedSprite);

	void setUV(Vector2i selectedSprite, Vector2i spriteSize);

	sf::RectangleShape returnShape();


	//Testing overriding an update function (Working)
	void Update(float deltaTime)
	{
		Component::Update(deltaTime);

		std::cout << "meowest" << std::endl;
	}

private:
	sf::RectangleShape shape;

	LLGP::Vector2<float> rectangleSize;

};
