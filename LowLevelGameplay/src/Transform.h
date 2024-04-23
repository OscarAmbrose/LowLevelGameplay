#pragma once
#include <Vector2.h>

namespace LLGP
{
	class Transform2D
	{
	public:
		Transform2D();
		Transform2D(LLGP::Vector2<float> pos, LLGP::Vector2<float> scal, float rot);

		//template<class T> requires isComponent<T> T* GetComponent();

		inline void setPosition(LLGP::Vector2<float> newPosition) { m_Position = newPosition; };
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

		inline LLGP::Vector2<float> returnPosition() { return m_Position; }
		inline LLGP::Vector2<float> returnScale() { return m_Scale; }
		inline float returnRotation() { return m_Rotation; }

	private:
		LLGP::Vector2<float> m_Position;
		LLGP::Vector2<float> m_Scale;
		float m_Rotation;

	};
}
