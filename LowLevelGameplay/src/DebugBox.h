#pragma once
#include <Component.h>
#include <SFML/Graphics.hpp>
#include <Vector2.h>

class DebugBox : public Component
{
public:
	DebugBox(GameObject* owner);
	~DebugBox();

	void SetUpDebugBox();

	void renderShape(sf::RenderWindow* window, int renderLayer);

protected:
	sf::RectangleShape m_Shape;
	LLGP::Vector2<float> m_RectangleSize = LLGP::Vector2f(0, 0);
	LLGP::Vector2f m_Offset = LLGP::Vector2f(0, 0);
	int m_RenderLayer;
};
