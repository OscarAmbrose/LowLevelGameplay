#pragma once
#include <Event.h>
#include <DispatcherTest1.h>

class ListenerTest
{
private:
	DispatcherTest* other;

public:
	ListenerTest(DispatcherTest* _other) : other(_other) { other->meowEvent += std::bind(&ListenerTest::Handle_MeowEvent, this, std::placeholders::_1); }

	void Handle_MeowEvent(int in)
	{
		//std::cout << in << std::endl;
		other->meowEvent -= std::bind(&ListenerTest::Handle_MeowEvent, this, std::placeholders::_1);
	}
};
