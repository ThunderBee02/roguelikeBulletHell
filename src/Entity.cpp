#include "Entity.h"

FloatCircle::FloatCircle(Vector2f center, float radius)
	: center(center), radius(radius)
{
}

bool FloatCircle::intersects(const FloatCircle& other) const
{
	return (other.center - center).length() <= other.radius + radius;
}

bool FloatCircle::intersects(Vector2f offset, const FloatCircle& other, Vector2f otherOffset) const
{
	return ((other.center + otherOffset) - (center + offset)).length() <= other.radius + radius;
}



Entity::Entity(int health, int damage)
	: health(health), damage(damage)
{
}

Vector2f Entity::getCenter() const
{
	return circle.getPosition();
}

Angle Entity::getRotation() const
{
	return circle.getRotation();
}

bool Entity::isOutside() const
{
	const FloatRect screen({ 0.f, 0.f }, { 1200.f, 900.f });
	if (screen.contains(getCenter()))
		return false;
	return true;
}

void Entity::move(Vector2f offset, Angle angle)
{
	circle.move(offset);
	circle.setRotation(angle);

	for (FloatCircle& circle : hitbox)
	{
		circle.center = circle.center.rotatedBy(angle);
	}
}
/*void Entity::move(Vector2f offset, Angle angle)	// using global hitbox coordinates
{
	for (FloatCircle& hitboxCircle : hitbox)
	{
		Vector2f local = hitboxCircle.center - getCenter();
		local = local.rotatedBy(angle);
		hitboxCircle.center = local + getCenter() + offset;
	}

	circle.move(offset);
	circle.setRotation(angle);
}*/

bool Entity::doDamage(vector<unique_ptr<Entity>>& targets) const
{
	for (auto it = targets.begin(); it != targets.end(); ++it)
	{
		if (checkCollision(**it))
		{
			if ((*it)->takeDamage(damage))
				targets.erase(it);
			return true;
		}
	}
	return false;
}

bool Entity::takeDamage(int damage)
{
	health -= damage;
	return health <= 0;
}
bool Entity::checkCollision(const Entity& other) const
{
	for (const FloatCircle& circle1 : hitbox)
		for (const FloatCircle& circle2 : other.hitbox)
			if (circle1.intersects(getCenter(), circle2, other.getCenter()))
				return true;
	return false;
}

void Entity::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(circle, states);
}
