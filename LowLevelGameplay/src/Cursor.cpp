#include "Cursor.h"
#include <SpriteRenderer.h>
#include <GameObject.h>
#include <Transform.h>
#include <WindowManager.h>
#include <BoxCollider.h>
#include <DebugBox.h>

Cursor::Cursor(GameObject* owner) : Component(owner)
{
	m_ControllerNumber = 1;
	m_JoystickDir = LLGP::Vector2f::zero;

	m_PlayerPos = _GameObject->GetTransform()->ReturnPosition();
	m_CursorPos = _GameObject->GetTransform()->ReturnPosition();

	m_RenderWindow = WindowManager::GetActiveWindow();
	m_RenderWindow->sf::Window::setMouseCursorVisible(false);

	m_SpriteRenderer = _GameObject->AddComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(13, 2), LLGP::Vector2i(64, 64))->setRenderLayer(3);

	m_BoxCollider = _GameObject->AddComponent<BoxCollider>()->SetUpCollider(LLGP::Vector2f(16, 16), LLGP::Vector2f(48, 48));
	m_BoxCollider->SetCollisionMask(0b10000000)->SetCollisionLayer(0b01000000);

	g_OnPollInputs.AddListener(this, std::bind(&Cursor::PollInput, this, std::placeholders::_1));
}

Cursor::~Cursor()
{
}

void Cursor::PollInput(sf::Event event)
{
	if (!GetGameObject()) { return; }

	switch (event.type)
	{
	case sf::Event::JoystickMoved:
	{
		if (!sf::Joystick::isConnected(m_ControllerNumber)) { return; }

		float axisZ = (sf::Joystick::getAxisPosition(m_ControllerNumber, sf::Joystick::U) / 100);
		float axisR = (sf::Joystick::getAxisPosition(m_ControllerNumber, sf::Joystick::V) / 100);

		if ((axisR < m_JoystickDeadzone && axisR > -m_JoystickDeadzone))
		{
			axisR = 0;
		}
		if ((axisZ < m_JoystickDeadzone && axisZ > -m_JoystickDeadzone))
		{
			axisZ = 0;
		}

		m_JoystickDir = LLGP::Vector2f(axisZ, axisR);
		std::cout << m_JoystickDir.x << ", " << m_JoystickDir.y << std::endl;
	}
	break;
	case sf::Event::JoystickDisconnected:
	{
		std::cout << "Controller disconnected: Id: " << event.joystickMove.joystickId << std::endl;
	}
	break;
	case sf::Event::JoystickConnected:
	{
		std::cout << "Controller connected: Id: " << event.joystickMove.joystickId << std::endl;
	}
	break;
	default:
	{
		break;
	}
	}
}

void Cursor::SetCursorPosition(LLGP::Vector2f location)
{
	auto CursorPosition = m_CursorPos - m_PlayerPos;

	auto test = FixCursorPosition(m_CursorPos - m_PlayerPos);

	m_SpriteRenderer->setOffSet(test);
}

LLGP::Vector2f Cursor::FixCursorPosition(LLGP::Vector2f position)
{
	if (position.x > (1920 - m_PlayerPos.x))
	{
		position.x = 1920.f - m_PlayerPos.x;
		m_CursorPos.x = 1920.f;

	}
	else if (position.x < (0 - m_PlayerPos.x))
	{
		position.x = 0 - m_PlayerPos.x;
		m_CursorPos.x = 0;

	}
	if (position.y < (0 - m_PlayerPos.y))
	{
		position.y = 0 - m_PlayerPos.y;
		m_CursorPos.y = 0;
	}
	else if (position.y > (1080 - m_PlayerPos.y))
	{
		position.y = 1080 - m_PlayerPos.y;
		m_CursorPos.y = 1080;
	}
	return position;
}

void Cursor::FixedUpdate(float deltaTime)
{
	m_PlayerPos = _GameObject->GetTransform()->ReturnPosition();

	m_CursorPos += m_JoystickDir * m_CursorMoveSpeed * deltaTime;
	SetCursorPosition(m_CursorPos);
}

void Cursor::Update(float deltaTime)
{

}
