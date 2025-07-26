#include "Weapon.h"
#include "Game.h"
#include <iostream>

Weapon::Weapon(int damage, float recoveryTime, Vector2f localOffset, EntityPool& selfPool, EntityPool& enemyPool)
	: damage(damage), recoveryTime(recoveryTime), localOffset(localOffset), selfPool(selfPool), enemyPool(enemyPool)
{
}


TargetedWeapon::TargetedWeapon(int damage, float recoveryTime, float projectileSpeed, Vector2f localOffset, EntityPool& selfPool, EntityPool& enemyPool)
	: Weapon(damage, recoveryTime, localOffset, selfPool, enemyPool), projectileSpeed(projectileSpeed)
{
}

void TargetedWeapon::update(float deltaTime, Vector2f origin, Angle angle)
{
	timeSinceShot += deltaTime;
	if (timeSinceShot >= recoveryTime)
	{
		timeSinceShot -= recoveryTime;

		Vector2f position(origin + localOffset.rotatedBy(angle));
		Vector2f closestTarget(600.f, -1000.f);
		float smallestDistance = 10000.f;
		for (const unique_ptr<Entity>& target : enemyPool.characters)
		{
			Vector2f targetPosition = target->getCenter();
			float distance = (targetPosition - position).length();
			if (distance < smallestDistance)
			{
				closestTarget = targetPosition;
				smallestDistance = distance;
			}
		}
		selfPool.generalProjectiles.push_back(make_unique<LinearProjectile>(damage, projectileSpeed, position, closestTarget-position, enemyPool));
	}
}


HomingWeapon::HomingWeapon(int damage, float recoveryTime, float projectileSpeed, bool destroyable, int projectileHealth, Angle maxTurn, Vector2f localOffset, EntityPool& selfPool, EntityPool& enemyPool)
	: Weapon(damage, recoveryTime, localOffset, selfPool, enemyPool), projectileSpeed(projectileSpeed), destroyable(destroyable), projectileHealth(projectileHealth), maxTurn(maxTurn)
{
}

HomingWeapon::HomingWeapon(int damage, float recoveryTime, float projectileSpeed, Angle maxTurn, Vector2f localOffset, EntityPool& selfPool, EntityPool& enemyPool)
	: HomingWeapon(damage, recoveryTime, projectileSpeed, false, 1, maxTurn, localOffset, selfPool, enemyPool)
{
}

void HomingWeapon::update(float deltaTime, Vector2f origin, Angle angle)
{
	timeSinceShot += deltaTime;
	if (timeSinceShot >= recoveryTime)
	{
		timeSinceShot -= recoveryTime;

		Vector2f spawnPoint(origin + localOffset.rotatedBy(angle));
		if (destroyable)
			selfPool.destroyableProjectiles.push_back(make_unique<HomingProjectile>(projectileHealth, damage, projectileSpeed, spawnPoint, maxTurn, enemyPool));
		else
			selfPool.generalProjectiles.push_back(make_unique<HomingProjectile>(damage, projectileSpeed, spawnPoint, maxTurn, enemyPool));
	}
}
