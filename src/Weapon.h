#pragma once
#include "Help.h"
#include "Projectile.h"

class Weapon
{
protected:
	float timeSinceShot = 0.f;
	float recoveryTime;
	int damage;

	Vector2f localOffset;
	EntityPool& selfPool;
	EntityPool& enemyPool;

	Weapon(int damage, float recoveryTime, Vector2f localOffset, EntityPool& selfPool, EntityPool& enemyPool);

public:
	virtual void update(float deltaTime, Vector2f origin, Angle angle) = 0;
};

class TargetedWeapon : public Weapon
{
private:
	float projectileSpeed;

public:
	TargetedWeapon(int damage, float recoveryTime, float projectileSpeed, Vector2f localOffset, EntityPool& selfPool, EntityPool& enemyPool);

	virtual void update(float deltaTime, Vector2f origin, Angle angle) override;
};

class HomingWeapon : public Weapon
{
private:
	float projectileSpeed;
	bool destroyable;
	int projectileHealth;
	Angle maxTurn;

public:
	HomingWeapon(int damage, float recoveryTime, float projectileSpeed, bool destroyable, int projectileHealth, Angle maxTurn, Vector2f localOffset, EntityPool& selfPool, EntityPool& enemyPool);
	HomingWeapon(int damage, float recoveryTime, float projectileSpeed, Angle maxTurn, Vector2f localOffset, EntityPool& selfPool, EntityPool& enemyPool);

	virtual void update(float deltaTime, Vector2f origin, Angle angle) override;
};