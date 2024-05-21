#pragma once
#include <Vector2.h>
#include <SFML/Graphics.hpp>
#include <Component.h>
#include <GlobalEvents.h>
//#include <AssetManager.h>
#include<GlobalTexture.h>

//class Transform2D;
class GameObject;

class SpriteRenderer : public Component
{
public:

	SpriteRenderer(GameObject* owner) : Component(owner) 
	{ 
		m_RenderLayer = 5;

		shape.setTexture(renderTexture);

		rectTexSize = LLGP::Vector2i(shape.getTexture()->getSize());

		//Vector2i selectedSprite = Vector2i(10, 15);
		LLGP::Vector2i selectedSprite = LLGP::Vector2i(0, 0);
		setUV(selectedSprite);

		g_OnRender.AddListener(this, std::bind(&SpriteRenderer::renderShape, this, std::placeholders::_1, std::placeholders::_2));
	}

	~SpriteRenderer()
	{
		std::cout << "Meow" << std::endl;
		g_OnRender.RemoveListener(this, std::bind(&SpriteRenderer::renderShape, this, std::placeholders::_1, std::placeholders::_2));
	}

	void setUV(LLGP::Vector2i selectedSprite);

	void setUV(LLGP::Vector2i selectedSprite, LLGP::Vector2i spriteSize);

	sf::RectangleShape returnShape();

	inline bool getFlipped() { return isFlipped; }
	void setFlipped(bool newFlipped);

	//void renderShape(float renderNum);
	void renderShape(sf::RenderWindow* window, int renderLayer);

	//Testing overriding an update function (Working)
	void Update(float deltaTime)
	{
		Component::Update(deltaTime);

		//std::cout << "meowest" << std::endl;
	}

	inline void setOffSet(LLGP::Vector2f newOffset) { offset = newOffset; }
	inline LLGP::Vector2f getOffset() { return offset; }

	inline void setRenderLayer(int newRenderLayer) { m_RenderLayer = newRenderLayer; }
	inline int getRenderLayer() { return m_RenderLayer; }

private:
	sf::RectangleShape shape;

	LLGP::Vector2<float> rectangleSize;

	LLGP::Vector2f offset = LLGP::Vector2f(0, 0);

	bool isFlipped = false;

	LLGP::Vector2i spritesInTexture = LLGP::Vector2i(32, 16);

	LLGP::Vector2i rectTexSize = LLGP::Vector2i(0, 0);

	int m_RenderLayer;
};
