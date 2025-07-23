#pragma once
#include "Help.h"
#include "Entity.h"
#include "MovementPattern.h"
#include "Weapon.h"

class Enemy : public Entity
{
private:
	unique_ptr<MovementPattern> movementPattern;
	vector<unique_ptr<Weapon>> weapons;

public:
	Enemy(int health, Vector2f spawnPoint, unique_ptr<MovementPattern>& movementPattern, vector<unique_ptr<Weapon>>& weapons);

	virtual bool update(float deltaTime) override;
};
