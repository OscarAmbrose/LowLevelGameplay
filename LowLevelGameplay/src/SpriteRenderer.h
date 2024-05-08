#pragma once
#include <Vector2.h>
#include <SFML/Graphics.hpp>
#include <Component.h>w
#include <memory>
#include <Event.h>
#include <GlobalEvents.h>
#include <AssetManager.h>
#include<Texture.h>

//class Transform2D;
class GameObject;

class SpriteRenderer : public Component
{
public:

	SpriteRenderer(GameObject* owner) : Component(owner) 
	{ 
		//std::shared_ptr<Texture> meow = LLGP::AssetManager::GetAsset<Texture>("Textures/JoustSpritesActual.png");
		//shape.setTexture(*meow.get());

		SetTexture();

		g_OnRender.AddListener(this, std::bind(&SpriteRenderer::renderShape, this, std::placeholders::_1));
	}

	~SpriteRenderer()
	{
		std::cout << "Meow" << std::endl;
		g_OnRender.RemoveListener(this, std::bind(&SpriteRenderer::renderShape, this, std::placeholders::_1));
	}
	
	void SetTexture();

	void setUV(Vector2i selectedSprite);

	void setUV(Vector2i selectedSprite, Vector2i spriteSize);

	sf::RectangleShape returnShape();

	//void renderShape(float renderNum);
	void renderShape(sf::RenderWindow* window);

	//Testing overriding an update function (Working)
	void Update(float deltaTime)
	{
		Component::Update(deltaTime);

		std::cout << "meowest" << std::endl;
	}

private:
	sf::RectangleShape shape;

	std::shared_ptr<Texture> texture;

	LLGP::Vector2<float> rectangleSize;

};
