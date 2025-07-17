#include "Help.h"

FloatCircle::FloatCircle(Vector2f center, float radius)
	: center(center), radius(radius)
{
}

bool FloatCircle::intersects(const FloatCircle& circle) const
{
	return (circle.center - center).length() <= circle.radius + radius;
}

bool FloatCircle::intersects(const CircleShape& circle) const
{
	return (circle.getPosition() - center).length() <= circle.getRadius() + radius;
}
