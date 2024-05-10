#pragma once
#include <Vector2.h>
#include <SFML/Graphics.hpp>
#include <Component.h>
#include <memory>
#include <Event.h>
#include <GlobalEvents.h>
//#include <AssetManager.h>
#include<Texture.h>
#include<GlobalTexture.h>

//class Transform2D;
class GameObject;

class SpriteRenderer : public Component
{
public:

	SpriteRenderer(GameObject* owner) : Component(owner) 
	{ 
		shape.setTexture(renderTexture);

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

	inline bool getFlipped() { return isFlipped; }
	inline void setFlipped(bool newFlipped) 
	{ 
		isFlipped = newFlipped;
		if (newFlipped)
		{
			shape.setScale(-1.f, 1.f);
		}
		else
		{
			shape.setScale(1.f, 1.f);
		}
	}

	//void renderShape(float renderNum);
	void renderShape(sf::RenderWindow* window);

	//Testing overriding an update function (Working)
	void Update(float deltaTime)
	{
		Component::Update(deltaTime);

		//std::cout << "meowest" << std::endl;
	}

	inline void setOffSet(LLGP::Vector2f newOffset) { offset = newOffset; }
	inline LLGP::Vector2f getOffset() { return offset; }

private:
	sf::RectangleShape shape;

	LLGP::Vector2<float> rectangleSize;

	LLGP::Vector2f offset = LLGP::Vector2f(0, 0);

	bool isFlipped = false;

};
