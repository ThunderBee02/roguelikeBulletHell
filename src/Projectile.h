#pragma once
#include "Help.h"
#include "Entity.h"
#include "Game.h"

class LinearProjectile : public Entity
{
private:
	Vector2f direction;
	float speed;

	EntityPool& enemyPool;

public:
	LinearProjectile(int damage, float speed, Vector2f spawnPoint, Vector2f direction, EntityPool& enemyPool);

	virtual bool update(float deltaTime) override;
};

class HomingProjectile : public Entity
{
private:
	Angle angle;
	float speed;
	Angle maxTurn;

	EntityPool& enemyPool;

	Vector2f getClosest(const vector<unique_ptr<Entity>>& targets) const;

public:
	HomingProjectile(int damage, float speed, Vector2f spawnPoint, Angle maxTurn, EntityPool& enemyPool);

	virtual bool update(float deltaTime) override;
};
