#pragma once
#include "Help.h"
#include "Entity.h"

class LinearProjectile : public Entity
{
private:
	Vector2f direction;
	float speed;
public:
	int damage;

	LinearProjectile(int damage, float speed, Vector2f position, Vector2f direction);

	virtual void update(float deltaTime) override;
};

class HomingProjectile : public Entity
{
private:
	Vector2f direction;
	float speed;
	float maxTurnSpeed;

	vector<unique_ptr<Entity>>& targets;
public:
	int damage;

	HomingProjectile(int damage, float speed, Vector2f position, vector<unique_ptr<Entity>>& targets);

	virtual void update(float deltaTime) override;
};
