#include "JoustPlayerCharacter.h"
#include "SpriteRenderer.h"
#include "AnimationManager.h"
#include "Transform.h"
#include "Collider.h"
#include "Physics.h"
#include "RigidBody.h"
#include <DebugBox.h>
#include <PlayerInputController.h>
#include <GlobalEvents.h>
#include <Event.h>
#include <ScreenWrapper.h>
#include <JoustAIController.h>


JoustPlayer::JoustPlayer() : Character()
{
	initialiseCharacter(0, 'c', 0b00000111, 0b00000010);
	AddComponent<PlayerInputController>()->getEvent<LLGP::Vector2<float>>("MoveDirection")->AddListener(this, std::bind(&Character::HandleInput, this, std::placeholders::_1));
}
