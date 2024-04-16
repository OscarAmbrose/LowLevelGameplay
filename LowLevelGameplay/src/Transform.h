#pragma once
#include <Vector2.h>

using namespace LLGP;

class Transform2D
{
public:
	Transform2D();
	Transform2D(Vector2<float> pos, Vector2<float> scal, float rot);

	//template<class T> requires isComponent<T> T* GetComponent();

	inline void setPosition(Vector2<float> newPosition) { m_Position = newPosition; };
	inline void setScale(Vector2<float> newScale) { m_Scale = newScale; };
	inline void setRotation(float newRotation);

	inline Vector2<float> returnPosition() { return m_Position; }
	inline Vector2<float> returnScale() { return m_Scale; }
	inline float returnRotation() { return m_Rotation; }

private:
	Vector2<float> m_Position;
	Vector2<float> m_Scale;
	float m_Rotation;

};
