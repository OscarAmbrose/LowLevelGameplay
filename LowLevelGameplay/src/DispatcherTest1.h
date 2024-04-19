#pragma once
#include <Event.h>
#include <iostream>

class DispatcherTest 
{
public:
	LLGP::Event<int> meowEvent;
	DispatcherTest() {
		meowEvent = LLGP::Event<int>();
	};

	void BroadcastOnMeowEvent(int arg1)
	{
		meowEvent(arg1);
	}
};
