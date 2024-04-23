#pragma once
#include <Vector2.h>
#include <SFML/Graphics.hpp>
#include <Component.h>
#include <memory>

//class Transform2D;
class GameObject;

class SpriteRenderer : public Component
{
public:

	SpriteRenderer(GameObject* owner, Transform2D* pTransform) : Component(owner, pTransform) 
	{ 
		//std::cout << parentTransform << std::endl;
		SetTexture("Textures/Test.png");
		CreateRect();
	}
	
	void SetTexture(std::string filePath)
	{
		renderTexture.reset();
		renderTexture = std::make_unique<sf::Texture>();
		//std::cout << filePath << std::endl;
		renderTexture.get()->loadFromFile(filePath);
		//std::cout << renderTexture.get() << "    1" << std::endl;
		shape.setTexture(renderTexture.get());
	}

	void CreateRect()
	{
		//shape.setFillColor(sf::Color::White);
	}

	sf::RectangleShape returnShape() 
	{
		LLGP::Vector2<float> rectSize = 100 * (parentTransform->returnScale());
		shape.setSize(rectSize);
		shape.setOrigin(rectSize / 2);
		shape.setRotation(parentTransform->returnRotation());

		shape.setPosition(LLGP::Vector2(450, 450)/*parentTransform->returnPosition()*/);

		return shape;
	}


private:
	sf::RectangleShape shape;
	std::unique_ptr<sf::Texture> renderTexture;
};
