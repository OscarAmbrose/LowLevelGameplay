#pragma once
#include <Event.h>

class DispatcherTest 
{
public:
	LLGP::Event<int> meowEvent;
	DispatcherTest() {};

	void BroadcastOnMeowEvent(int arg1)
	{
		meowEvent(arg1);
	}
};
