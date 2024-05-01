#include <Transform.h>
#include <GlobalEvents.h> 
#include "Component.h"
#include <GameObject.h>

Component::Component(GameObject* owner) : _GameObject(owner)
{
	/*parentTransform = pTransform;*/
	parentTransform = _GameObject->getTransform();
	g_OnUpdate.AddListener(this, std::bind(&Component::Update, this, std::placeholders::_1));
	g_OnStart.AddListener(this, std::bind(&Component::Start, this, std::placeholders::_1));
	g_OnFixedUpdate.AddListener(this, std::bind(&Component::FixedUpdate, this, std::placeholders::_1));
}

Component::~Component()
{
	g_OnUpdate.RemoveListener(this, std::bind(&Component::Update, this, std::placeholders::_1));
	g_OnFixedUpdate.RemoveListener(this, std::bind(&Component::FixedUpdate, this, std::placeholders::_1));
	g_OnStart.RemoveListener(this, std::bind(&Component::Start, this, std::placeholders::_1));

}

void Component::Start(float start)
{
	g_OnStart.RemoveListener(this, std::bind(&Component::Start, this, std::placeholders::_1));
	std::cout << "Start" << std::endl;

}

void Component::Update(float deltaTime)
{
	std::cout << "Update: " << deltaTime << std::endl;
}

void Component::FixedUpdate(float deltaTime)
{
	std::cout << "Fixed Update: " << deltaTime << std::endl;
}
