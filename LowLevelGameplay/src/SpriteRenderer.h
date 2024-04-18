#pragma once
#include <Vector2.h>
#include <SFML/Graphics.hpp>
#include <Component.h>
#include <Vector2.h>
#include<Transform.h>
#include <iostream>

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject* m_Parent) : Component(m_Parent) { std::cout << GetGameObject(); }

	void Initialise();
};
