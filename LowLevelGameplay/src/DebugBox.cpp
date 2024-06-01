#pragma once
#include "DebugBox.h"
#include <GameObject.h>
#include <SpriteRenderer.h>
#include <BoxCollider.h>
#include <Transform.h>

DebugBox::DebugBox(GameObject* owner) : Component(owner)
{
	m_RenderLayer = 0;

	m_Shape.setFillColor(sf::Color::Transparent);
	m_Shape.setOutlineColor(sf::Color::Red);
	m_Shape.setOutlineThickness(3.f);

	m_Shape.setSize(m_RectangleSize);
	m_Shape.setOrigin(m_RectangleSize / 2);
}


DebugBox::~DebugBox()
{
	g_OnRender.RemoveListener(this, std::bind(&DebugBox::renderShape, this, std::placeholders::_1, std::placeholders::_2));
}

void DebugBox::SetUpDebugBox()
{
	m_RectangleSize = _GameObject->GetComponent<BoxCollider>()->GetBoxSize();
	m_RenderLayer = 4;
	m_Shape.setFillColor(sf::Color::Transparent);
	m_Shape.setOutlineColor(sf::Color::Red);
	m_Shape.setOutlineThickness(1.f);

	m_Shape.setSize(m_RectangleSize);
	m_Shape.setOrigin(m_RectangleSize / 2);

	
	g_OnRender.AddListener(this, std::bind(&DebugBox::renderShape, this, std::placeholders::_1, std::placeholders::_2));
}

void DebugBox::renderShape(sf::RenderWindow* window, int renderLayer)
{
	//LLGP::Vector2f position = _GameObject->getTransform()->ReturnPosition();

	LLGP::Vector2f position = _GameObject->GetComponent<BoxCollider>()->GetBoxPosition()/* + _GameObject->GetComponent<BoxCollider>()->GetOffset()*/;

	m_RectangleSize = _GameObject->GetComponent<BoxCollider>()->GetBoxSize();

	m_Shape.setSize(m_RectangleSize);
	m_Shape.setOrigin(m_RectangleSize / 2);

	m_Shape.setPosition(position);

	if (renderLayer == m_RenderLayer)
	{
		window->draw(m_Shape);
	}
}


