#pragma once
#include <Vector2.h>
//#include <Component.h>

//class Component;
class GameObject;

class Transform2D /*: public Component*/
{
public:
	Transform2D(/*GameObject* owner*/)/* : Component(owner)*/ {
		m_Rotation = 0.0f;
		m_Position = LLGP::Vector2<float>(750, 500);
		m_Scale = LLGP::Vector2<float>(1, 1);
	};

	~Transform2D() {};

	inline void setPosition(LLGP::Vector2<float> newPosition) { m_Position = newPosition; }
	inline void setScale(LLGP::Vector2<float> newScale) { m_Scale = newScale; };
	inline void setRotation(float newRotation)
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
	};

	inline LLGP::Vector2<float> ReturnPosition() { return m_Position; }
	inline LLGP::Vector2<float> returnScale() { return m_Scale; }
	inline float returnRotation() { return m_Rotation; }

private:
	LLGP::Vector2<float> m_Position;
	LLGP::Vector2<float> m_Scale;
	float m_Rotation;

};

