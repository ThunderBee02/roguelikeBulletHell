#pragma once
#include "Help.h"
#include "MovementPattern.h"
#include "Weapon.h"
#include "Player.h"

class Enemy : public Drawable
{
protected:
	Texture texture;
	CircleShape circle;

	unique_ptr<MovementPattern> movementPattern;
	vector<unique_ptr<Weapon>> weapons;

	int health;

public:
	Enemy(int health, Vector2f spawnPoint, unique_ptr<MovementPattern>& movementPattern, vector<unique_ptr<Weapon>>& weapons);

	void update(float deltaTime, Player& player);

	virtual void draw(RenderTarget& target, RenderStates states) const override;
};
