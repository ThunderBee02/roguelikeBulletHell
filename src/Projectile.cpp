#include "Projectile.h"
#include <iostream>

LinearProjectile::LinearProjectile(int damage, float speed, Vector2f position, Vector2f direction, EntityPool& enemyPool)
	: Entity(1, damage), speed(speed), direction(direction.normalized()), enemyPool(enemyPool)
{
	circle.setPointCount(3);
	circle.setRadius(10.f);
	circle.setOrigin({ 10.f, 10.f });
	circle.setPosition(position);
	circle.setFillColor(Color(255, 0, 0));
	circle.setRotation(direction.angle()-degrees(30));

	hitbox.emplace_back(Vector2f(0.f, 0.f), 10.f);
}

bool LinearProjectile::update(float deltaTime)
{
	move(direction * speed * deltaTime, getRotation());

	return doDamage(enemyPool.characters) || doDamage(enemyPool.destroyableProjectiles);
}

HomingProjectile::HomingProjectile(int damage, float speed, Vector2f position, Angle maxTurn, EntityPool& enemyPool)
	: Entity(1, damage), speed(speed), maxTurn(maxTurn), enemyPool(enemyPool)
{
	circle.setPointCount(3);
	circle.setRadius(10.f);
	circle.setOrigin({ 10.f, 10.f });
	circle.setPosition(position);
	circle.setFillColor(Color(255, 0, 128));
	
	angle = (getClosest(enemyPool.characters) - getCenter()).angle();
	circle.setRotation(angle - degrees(30));

	hitbox.emplace_back(Vector2f(0.f, 0.f), 10.f);
}

Vector2f HomingProjectile::getClosest(const vector<unique_ptr<Entity>>& targets) const
{
	Vector2f closestTarget(600.f, -1000.f);
	float smallestDistance = 10000.f;
	for (const unique_ptr<Entity>& target : targets)
	{
		Vector2f targetPosition = target->getCenter();
		float distance = (targetPosition - getCenter()).length();
		if (distance < smallestDistance)
		{
			closestTarget = targetPosition;
			smallestDistance = distance;
		}
	}
	return closestTarget;
}

bool HomingProjectile::update(float deltaTime)
{
	Angle newAngle = (getClosest(enemyPool.characters) - getCenter()).angle();
	Angle diffAngle = (newAngle - angle).wrapSigned();
	Angle maxTurn = degrees(50.f) * deltaTime;
	clamp(diffAngle, maxTurn);
	angle += diffAngle;

	Vector2f unitVector(1.f, 0.f);
	move(unitVector.rotatedBy(angle) * speed * deltaTime, angle - degrees(30));

	return doDamage(enemyPool.characters);
}
