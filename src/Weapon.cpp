#include "Weapon.h"
#include "Game.h"

extern Game game;

Weapon::Weapon(float recoveryTime, int damage)
	: recoveryTime(recoveryTime), timeSinceShot(0.f), damage(damage)
{
}

void Weapon::draw(RenderTarget& target, RenderStates states) const
{
	for (const Projectile& projectile : projectiles)
	{
		target.draw(projectile, states);
	}
}



linearWeapon::linearWeapon(float recoveryTime, int damage, float projectileSpeed)
	: Weapon(recoveryTime, damage), projectileSpeed(projectileSpeed)
{
}

void linearWeapon::update(float deltaTime, Vector2f origin, Vector2f target)
{
	timeSinceShot += deltaTime;
	if (timeSinceShot >= recoveryTime)
	{
		timeSinceShot = 0.f;
		projectiles.emplace_back(10.f, origin, (target - origin).normalized());
	}

	for (Projectile& projectile : projectiles)
	{
		projectile.move(projectile.direction * projectileSpeed * deltaTime);
	}

	projectiles.erase(remove_if(projectiles.begin(), projectiles.end(),
		[](Projectile& projectile) {
			return projectile.cull();
		}), projectiles.end());
}
