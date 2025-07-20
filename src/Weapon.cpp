#include "Weapon.h"
#include "Game.h"
#include <iostream>



Weapon::Weapon(int damage, float recoveryTime, Vector2f localPosition, vector<unique_ptr<Entity>>& projectiles)
	: damage(damage), recoveryTime(recoveryTime), localPosition(localPosition), projectiles(projectiles)
{
}


TargetedWeapon::TargetedWeapon(int damage, float recoveryTime, float projectileSpeed, Vector2f localPosition, vector<unique_ptr<Entity>>& projectiles, vector<unique_ptr<Entity>>& targets)
	: Weapon(damage, recoveryTime, localPosition, projectiles), projectileSpeed(projectileSpeed), targets(targets)
{
}

void TargetedWeapon::update(float deltaTime, Vector2f origin, Angle angle)
{
	timeSinceShot += deltaTime;
	if (timeSinceShot >= recoveryTime)
	{
		timeSinceShot = 0.f;
		Vector2f position(origin + localPosition.rotatedBy(angle));
		Vector2f closestTarget(600.f, -1000.f);
		float smallestDistance = 10000.f;
		for (const unique_ptr<Entity>& target : targets)
		{
			Vector2f targetPosition = target->getCenter();
			float distance = (targetPosition - position).length();
			if (distance <= smallestDistance)
			{
				closestTarget = targetPosition;
				smallestDistance = distance;
			}
		}
		projectiles.push_back(make_unique<LinearProjectile>(damage, projectileSpeed, position, closestTarget-position));
	}
	
}
