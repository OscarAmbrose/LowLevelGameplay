#pragma once
#include <Event.h>

class Timer
{
public:
	Timer(float Timer);
	~Timer();

	void Update(float deltaTime);
	void StartTimer(float deltaTime);

	float GetMaxTime() const { return _MaxTimer; }
	void ClearAndInvalidateTimer();
	float GetTimeRemaining() const { return (_MaxTimer - _ElapsedTime); }
	float GetElapsedTime() const { return _ElapsedTime; }

	void EndTimer(bool norm);

public:
	LLGP::Event<int> TimerFinished;

private:
	float _ElapsedTime;
	float _MaxTimer;
	bool _TimerEndedNorm = false;
	bool _TimerEnded = false;
};