#include "Transform.h"

LLGP::Transform2D::Transform2D()
{
	m_Rotation = 0.0f;
	m_Position = Vector2<float>(750, 500);
	m_Scale = Vector2<float>(1, 1);
}

LLGP::Transform2D::Transform2D(Vector2<float> pos, Vector2<float> scal, float rot)
{
	m_Rotation = rot;
	m_Position = pos;
	m_Scale = scal;
}

