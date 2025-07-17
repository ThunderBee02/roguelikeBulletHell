#include "Projectile.h"

Projectile::Projectile(float radius, Vector2f position, Vector2f direction)
	: circle(radius, 8), direction(direction)
{
	circle.setOrigin({ radius, radius });
	circle.setPosition(position);
	circle.setFillColor(Color(255, 0, 0));
}

bool Projectile::cull() const
{
	const FloatRect screen({ 0.f, 0.f }, { 1200.f, 900.f });
	if (screen.contains(circle.getPosition()))
		return false;
	return true;
}

void Projectile::move(Vector2f offset)
{
	circle.move(offset);
}

void Projectile::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(circle, states);
}
