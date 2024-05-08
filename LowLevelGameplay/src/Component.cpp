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
	std::cout << "Start" << std::endl;
}

void Component::Update(float deltaTime)
{
	//Ensure Start is only called once:
	if (!Started)
	{
		g_OnStart.RemoveListener(this, std::bind(&Component::Start, this, std::placeholders::_1));
		Started = true;
	}

}

void Component::FixedUpdate(float deltaTime)
{
	
}
