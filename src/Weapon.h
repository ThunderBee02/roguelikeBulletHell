#pragma once
#include "Help.h"
#include "Projectile.h"

class Weapon
{
protected:
	float timeSinceShot = 0.f;
	float recoveryTime;
	int damage;
	Vector2f localPosition;
	vector<unique_ptr<Entity>>& projectiles;

	Weapon(int damage, float recoveryTime, Vector2f localPosition, vector<unique_ptr<Entity>>& projectiles);

public:
	virtual void update(float deltaTime, Vector2f origin, Angle angle) = 0;
};

class TargetedWeapon : public Weapon
{
private:
	float projectileSpeed;
	vector<unique_ptr<Entity>>& targets;
public:
	TargetedWeapon(int damage, float recoveryTime, float projectileSpeed, Vector2f localPosition, vector<unique_ptr<Entity>>& projectiles, vector<unique_ptr<Entity>>& targets);

	virtual void update(float deltaTime, Vector2f origin, Angle angle) override;
};
