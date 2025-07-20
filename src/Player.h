#pragma once
#include "Help.h"
#include "Entity.h"
#include "Weapon.h"

class Player : public Entity
{
private:
	vector<unique_ptr<Weapon>> weapons;

public:
	Player();

	void update(float deltaTime);
};
