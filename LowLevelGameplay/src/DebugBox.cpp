#pragma once
#include "DebugBox.h"
#include <GameObject.h>
#include <SpriteRenderer.h>
#include <BoxCollider.h>
#include <Transform.h>

DebugBox::DebugBox(GameObject* owner) : Component(owner)
{
	m_RenderLayer = 0;

	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(3.f);

	shape.setSize(rectangleSize);
	shape.setOrigin(rectangleSize / 2);
}


DebugBox::~DebugBox()
{
	g_OnRender.RemoveListener(this, std::bind(&DebugBox::renderShape, this, std::placeholders::_1, std::placeholders::_2));
}

void DebugBox::SetUpDebugBox()
{
	rectangleSize = _GameObject->GetComponent<BoxCollider>()->GetBoxSize();
	m_RenderLayer = 0;
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.f);

	shape.setSize(rectangleSize);
	shape.setOrigin(rectangleSize / 2);

	
	g_OnRender.AddListener(this, std::bind(&DebugBox::renderShape, this, std::placeholders::_1, std::placeholders::_2));
}

void DebugBox::renderShape(sf::RenderWindow* window, int renderLayer)
{
	//LLGP::Vector2f position = _GameObject->getTransform()->returnPosition();

	LLGP::Vector2f position = _GameObject->GetComponent<BoxCollider>()->GetBoxPosition() + _GameObject->GetComponent<BoxCollider>()->GetOffset();

	rectangleSize = _GameObject->GetComponent<BoxCollider>()->GetBoxSize();

	shape.setSize(rectangleSize);
	shape.setOrigin(rectangleSize / 2);

	shape.setPosition(position);

	if (renderLayer == m_RenderLayer)
	{
		window->draw(shape);
	}
}


