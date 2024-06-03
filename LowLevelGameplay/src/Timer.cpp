#include <Timer.h>
#include <GlobalEvents.h>

Timer::Timer(float Timer)
{
	_TimerEndedNorm = true;
	_TimerEnded = true;
	_ElapsedTime = 0;
	_MaxTimer = Timer;
}

Timer::~Timer()
{
	TimerFinished.Empty();
	g_OnUpdate.RemoveListener(this, std::bind(&Timer::Update, this, std::placeholders::_1));
}



void Timer::Update(float deltaTime)
{
	if (_TimerEnded == true) { return; }
	_ElapsedTime += deltaTime;
	if (_ElapsedTime >= _MaxTimer)
	{
		EndTimer(true);
	}
}

void Timer::StartTimer(float deltaTime)
{
	g_OnUpdate.AddListener(this, std::bind(&Timer::Update, this, std::placeholders::_1));
	_ElapsedTime = 0.f;
	_TimerEnded = false;
}

void Timer::ClearAndInvalidateTimer()
{
	EndTimer(false);
}

void Timer::EndTimer(bool norm)
{
	_TimerEnded = true;
	_ElapsedTime = 0.f;
	TimerFinished.Invoke(norm);
}
