#include "Cursor.h"
#include <SpriteRenderer.h>
#include <GameObject.h>
#include <Transform.h>
#include <WindowManager.h>

#include <BoxCollider.h>
#include <DebugBox.h>

Cursor::Cursor(GameObject* owner) : Component(owner)
{
	m_RenderWindow = WindowManager::GetActiveWindow();
	m_RenderWindow->sf::Window::setMouseCursorVisible(false);
	renderer = _GameObject->AddComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(13, 2), LLGP::Vector2i(64, 64))->setRenderLayer(4);
	renderer2 = _GameObject->AddComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(10, 2))->setRenderLayer(3);
	
	
	box = _GameObject->AddComponent<BoxCollider>()->SetUpCollider(LLGP::Vector2f(16, 16), LLGP::Vector2f(48, 48));
	box->SetCollisionMask(0b10000000)->SetCollisionLayer(0b01000000);
	//_GameObject->AddComponent<DebugBox>()->SetUpDebugBox();
	g_OnPollInputs.AddListener(this, std::bind(&Cursor::PollInput, this, std::placeholders::_1));
}

Cursor::~Cursor()
{
}

void Cursor::PollInput(sf::Event event)
{
	if (!GetGameObject()) { return; }

	LLGP::Vector2f offset;
	//offset += -(GetGameObject()->GetTransform()->returnPosition());
	offset.x += sf::Mouse::getPosition().x;
	offset.y += sf::Mouse::getPosition().y;
	offset.x -= (renderer->GetRectangleSize().x / 8);
	offset.y -= (renderer->GetRectangleSize().y / 2);

	box->SetOffset(offset);
	renderer->setOffSet(offset);
	renderer2->setOffSet(offset);
}

void Cursor::FixedUpdate(float deltaTime)
{
	
}
