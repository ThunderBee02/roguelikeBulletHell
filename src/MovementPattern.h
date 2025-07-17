#pragma once
#include "Help.h"

class MovementPattern
{
protected:

public:
	virtual void update(float deltaTime, Vector2f position) = 0;
};
