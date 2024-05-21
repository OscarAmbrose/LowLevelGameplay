#pragma once
#include <Component.h>
#include <SFML/Graphics.hpp>
#include <Vector2.h>

class DebugBox : public Component
{
public:
	DebugBox(GameObject* owner);
	~DebugBox();

	//void Update(float deltaTime);

	//void Start(float deltaTime);

	void SetUpDebugBox();

	void renderShape(sf::RenderWindow* window, int renderLayer);

protected:
	sf::RectangleShape shape;
	LLGP::Vector2<float> rectangleSize = LLGP::Vector2f(0, 0);
	LLGP::Vector2f offset = LLGP::Vector2f(0, 0);
	int m_RenderLayer;
};
