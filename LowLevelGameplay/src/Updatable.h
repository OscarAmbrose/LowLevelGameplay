#pragma once

class Updatable
{
public:
	Updatable();
	virtual void update();
	virtual void fixedUpdate();
};
