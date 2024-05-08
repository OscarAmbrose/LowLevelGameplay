#pragma once
#include <memory>
#include <vector>
#include <Vector2.h>
#include <iostream>

class AnimationManager;

class AnimationState
{
public:
	AnimationState(AnimationManager* animManager);

	~AnimationState();

	void addAnimation(std::vector<LLGP::Vector2i> animation);

	void nextAnimTest(float deltaTime)
	{
		currentTime += deltaTime;
		if (currentTime < 0.2)
		{
			return;
		}
		int initPos = currentAnimPos;
		currentTime = 0;
		for (int i = 0; i < m_animationPositions.size(); i++)
		{
			if (m_animationPositions[i].x == currentAnimPos && m_animationPositions[i+1].x != 1024)
			{
				currentAnimPos = m_animationPositions[i + 1].x;
				updateRenderer(m_animationPositions[i + 1]);
				std::cout << currentAnimPos << std::endl;

				break;
			}
			
		}
		if (currentAnimPos == initPos)
		{
			currentAnimPos = 0;
			updateRenderer(LLGP::Vector2i(currentAnimPos, 0));
			std::cout << currentAnimPos << std::endl;
		}
	}

	void updateRenderer(LLGP::Vector2i position);
	void updateRenderer(LLGP::Vector2i position, LLGP::Vector2i size);
	//void updateRenderer(LLGP::Vector2i position);


protected:
	std::vector<LLGP::Vector2i> m_animationPositions;

	AnimationManager* m_animationManager;

	int currentAnimPos;

	float currentTime = 0;
};
