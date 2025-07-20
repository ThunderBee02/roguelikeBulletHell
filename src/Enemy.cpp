#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(int health, Vector2f spawnPoint, unique_ptr<MovementPattern>& movementPattern, vector<unique_ptr<Weapon>>& weapons)
	: health(health), movementPattern(std::move(movementPattern)), weapons(std::move(weapons))
{
	circle.setPointCount(5);
	circle.setRadius(100.f);
	circle.setOrigin({ 100.f, 100.f });
	circle.setPosition(spawnPoint);
	circle.setFillColor(Color(128, 0, 0));

	this->weapons.push_back(make_unique<TargetedWeapon>(3, 0.1f, 400.f, Vector2f(100.f,0.f), Game::enemyProjectiles, Game::players));
	//this->weapons.emplace_back(TargetedWeapon(0.25f, 3, 600.f));
}

void Enemy::update(float deltaTime)
{
	for (auto& weapon : weapons)
		weapon->update(deltaTime, getCenter(), getRotation());
}
