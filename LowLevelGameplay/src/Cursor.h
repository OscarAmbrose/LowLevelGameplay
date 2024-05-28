#pragma once
#include <Component.h>
#include <SFML/Graphics.hpp>

class SpriteRenderer;
class BoxCollider;

class Cursor : public Component
{
public:
	Cursor(GameObject* owner);
	~Cursor();

	inline sf::Window* GetWindow() { return m_RenderWindow; }

	void PollInput(sf::Event event);

	void FixedUpdate(float deltaTime);

protected:
	sf::Window* m_RenderWindow = nullptr;

	SpriteRenderer* renderer = nullptr;
	SpriteRenderer* renderer2 = nullptr;

	BoxCollider* box = nullptr;
};
