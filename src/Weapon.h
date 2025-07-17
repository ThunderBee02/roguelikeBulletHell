#pragma once
#include "Help.h"
#include "Projectile.h"

class Weapon : public Drawable
{
protected:
	float recoveryTime, timeSinceShot;
	int damage;
	vector<Projectile> projectiles;

	Weapon(float recoveryTime, int damage);

public:
	virtual void update(float deltaTime, Vector2f origin, Vector2f target) = 0;

	virtual void draw(RenderTarget& target, RenderStates states) const override;
};

class linearWeapon : public Weapon
{
private:
	float projectileSpeed;
public:
	linearWeapon(float recoveryTime, int damage, float projectileSpeed);

	virtual void update(float deltaTime, Vector2f origin, Vector2f target) override;
};
