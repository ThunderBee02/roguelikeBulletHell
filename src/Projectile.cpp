#include "Projectile.h"

LinearProjectile::LinearProjectile(int damage, float speed, Vector2f position, Vector2f direction)
	: damage(damage), speed(speed), direction(direction.normalized())
{
	circle.setPointCount(3);
	circle.setRadius(10.f);
	circle.setOrigin({ 10.f, 10.f });
	circle.setPosition(position);
	circle.setFillColor(Color(255, 0, 0));
	circle.setRotation(direction.angle()-degrees(30));
}

void LinearProjectile::update(float deltaTime)
{
	move(direction * speed * deltaTime, getRotation());
}
