#pragma once
#include "AnimationState.h"
#include "AnimationManager.h"

//Constructor
AnimationState::AnimationState(AnimationManager* animManager)
{
	//Sets default anim manager reference
	m_animationManager = animManager;
	
	//We want each animation state to be false in the beginning as they are added, when we add a animation this can be set to true.
	m_Active = false;
	
	//Default animation start is 0
	//currentAnimPos = 0;
	m_activeAnimation = 0;
}

//Deconstructor
AnimationState::~AnimationState()
{
	g_OnFixedUpdate.RemoveListener(this, std::bind(&AnimationState::UpdateAnimation, this, std::placeholders::_1));
}

void AnimationState::playAnimation(std::string animationName)
{
	Animation* animationToPlay = findAnimation(animationName);
	if (animationToPlay == nullptr)
	{
		std::cout << "AnimationState::playAnimation failed. Could not find animation." << std::endl;
		return;
	}

}

// Sets the active bool and deals with event dispatchers
void AnimationState::setActive(bool newActive)
{
	//Check if we need to do anything at all.
	if (m_Active == newActive) { return; }
	//If we do, first resolve true.
	else if (newActive == true) 
	{
		m_Active = true;
		g_OnFixedUpdate.AddListener(this, std::bind(&AnimationState::UpdateAnimation, this, std::placeholders::_1));
		return;
	}
	//Otherwise resolve false. Technically I could remove this else, but I think it improves readability.
	else
	{
		g_OnFixedUpdate.RemoveListener(this, std::bind(&AnimationState::UpdateAnimation, this, std::placeholders::_1));
	}
}

void AnimationState::speedBasedAnimation(float Speed, float deltaTime)
{
	distanceTravelled += Speed * deltaTime;
	//std::cout << distanceTravelled << std::endl;
	if (distanceTravelled >= (getSpriteRenderer()->returnShape().getSize().x * (4.5 / 32)))
	{
		updateRenderer(m_animations[m_activeAnimation]->getNextFrame());
		distanceTravelled -= (getSpriteRenderer()->returnShape().getSize().x * (4.5 / 32));
	}
}

void AnimationState::iterateAnimation()
{

}



//Just update the Renderer as a normal Tiled sprite (99% of usecase for the animator)
void AnimationState::updateRenderer(LLGP::Vector2i position)
{
	getSpriteRenderer()->setUV(position);
}

//Update animation for larger sprites (might see no use if pterodactly doesnt change
void AnimationState::updateRenderer(LLGP::Vector2i position, LLGP::Vector2i size)
{
	getSpriteRenderer()->setUV(position, size);
}

//Here will be the third sprite animation version when I animate the burning platform


//Animation update function, I figured update it better than fixed update for this.
//But it might be better to change this to fixed update, as animations shouldn't change without the physics change.
void AnimationState::UpdateAnimation(float deltaTime)
{
	//std::cout << "Hey Im an updating Animation" << std::endl;
	speedBasedAnimation(18, deltaTime);
}

inline SpriteRenderer* AnimationState::getSpriteRenderer()
{
	return m_animationManager->returnSpriteRenderer();
}

