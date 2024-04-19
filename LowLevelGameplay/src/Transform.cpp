#include "Transform.h"

LLGP::Transform2D::Transform2D()
{
	m_Rotation = 0.0f;
	m_Position = Vector2<float>(0, 0);
	m_Scale = Vector2<float>(100, 100);
}

LLGP::Transform2D::Transform2D(Vector2<float> pos, Vector2<float> scal, float rot)
{
	m_Rotation = rot;
	m_Position = pos;
	m_Scale = scal;
}

inline void LLGP::Transform2D::setRotation(float newRotation)
{
	while (newRotation > 360 || newRotation < 0)
	{
		if (newRotation > 360) 
		{
			newRotation -= 360;
		}
		else if (newRotation < 0)
		{
			newRotation += 360;
		}
	}

	m_Rotation = newRotation;
}
