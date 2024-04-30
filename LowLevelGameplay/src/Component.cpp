#include <Transform.h>
#include <GlobalEvents.h> 
#include "Component.h"
#include <GameObject.h>

Component::Component(GameObject* owner) : _GameObject(owner)
{
	/*parentTransform = pTransform;*/
	parentTransform = _GameObject->getTransform();
	g_OnUpdate.AddListener(this, std::bind(&Component::Update, this, std::placeholders::_1));
}

Component::~Component()
{
	g_OnUpdate.RemoveListener(this, std::bind(&Component::Update, this, std::placeholders::_1));
}

void Component::Update(float deltaTime)
{
	std::cout << "WOOOOOOOOOOOOOOOOOOOOOOO" << std::endl;
}
