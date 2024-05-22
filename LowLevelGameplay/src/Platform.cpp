#include "Platform.h"
#include <SpriteRenderer.h>
#include <BoxCollider.h>
#include <DebugBox.h>
#include <Transform.h>
#include <random>

Platform::Platform()
{
	AddComponent<SpriteRenderer>()->setRenderLayer(0);
}

Platform::~Platform()
{
}

bool Platform::randomBool()
{
	return 0 + (rand() % (1 - 0 + 1)) == 1;
}

std::shared_ptr<Platform> Platform::CreatePlatformType1(LLGP::Vector2f platformLocation)
{
	std::shared_ptr<Platform> platform = std::make_shared<Platform>();
	(platform.get())->SetPlatformInformation(LLGP::Vector2i(6, 10), LLGP::Vector2i(176, 18));
	(platform.get())->GetTransform()->setPosition(platformLocation);
	if (randomBool())
	{
		(platform.get())->GetComponent<SpriteRenderer>()->setFlipped(true);
	}
	return platform;
}

std::shared_ptr<Platform> Platform::CreateCeiling()
{
	std::shared_ptr<Platform> platform = std::make_shared<Platform>();
	(platform.get())->AddComponent<BoxCollider>()->SetUpCollider(LLGP::Vector2f(1920, 10), LLGP::Vector2f(0, 0));
	(platform.get())->GetTransform()->setPosition(LLGP::Vector2f(960, -10));
	(platform.get())->GetComponent<SpriteRenderer>()->setUV(LLGP::Vector2i(13, 13));
	return platform;
}

Platform* Platform::SetPlatformInformation(LLGP::Vector2i platformStart, LLGP::Vector2i platformSize)
{
	m_PlatformSize = LLGP::Vector2f(platformSize.x, platformSize.y);
	GetComponent<SpriteRenderer>()->setUV(platformStart, platformSize);
	AddComponent<BoxCollider>()->SetUpCollider(m_PlatformSize, LLGP::Vector2f(0, 0));
	
	return this;
}

void Platform::AddDebugBox()
{
	AddComponent<DebugBox>()->SetUpDebugBox();
}


