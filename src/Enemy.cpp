#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(int health, Vector2f spawnPoint, unique_ptr<MovementPattern>& movementPattern, vector<unique_ptr<Weapon>>& weapons)
	: Entity(health, 1), movementPattern(std::move(movementPattern)), weapons(std::move(weapons))
{
	circle.setPointCount(5);
	circle.setRadius(100.f);
	circle.setOrigin({ 100.f, 100.f });
	circle.setPosition(spawnPoint);
	circle.setFillColor(Color(128, 0, 0));

	hitbox.emplace_back(Vector2f(0.f, 0.f), 100.f);
	
	this->weapons.push_back(make_unique<TargetedWeapon>(1, 0.5f, 200.f, Vector2f(100.f, 0.f), Game::enemyEntities, Game::playerEntities));
	this->weapons.push_back(make_unique<HomingWeapon>(1, 0.6f, 300.f, true, 2, degrees(50), Vector2f(0.f, 100.f), Game::enemyEntities, Game::playerEntities));
}

bool Enemy::update(float deltaTime)
{
	for (auto& weapon : weapons)
		weapon->update(deltaTime, getCenter(), getRotation());
	return doDamage(Game::playerEntities.characters);
}
