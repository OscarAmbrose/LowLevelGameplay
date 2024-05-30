#pragma once
#include <Component.h>
#include <SFML/Graphics.hpp>
#include <Vector2.h>

class SpriteRenderer;
class BoxCollider;

class Cursor : public Component
{
public:
	Cursor(GameObject* owner);
	~Cursor();

	inline sf::Window* GetWindow() { return m_RenderWindow; }

	void PollInput(sf::Event event);

	void SetCursorPosition(LLGP::Vector2f location);

	LLGP::Vector2f FixCursorPosition(LLGP::Vector2f position);

	void FixedUpdate(float deltaTime);

	Cursor* SetControllerNumber(int newNum) { m_ControllerNumber = newNum; return this; }

protected:
	sf::Window* m_RenderWindow = nullptr;

	SpriteRenderer* m_SpriteRenderer = nullptr;

	LLGP::Vector2f m_JoystickDir;

	BoxCollider* m_BoxCollider = nullptr;

	int m_ControllerNumber;

	float m_JoystickDeadzone = 0.12f;

	float m_CursorMoveSpeed = 700.f;
};
