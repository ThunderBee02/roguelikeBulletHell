#include "Enemy.h"
#include "Game.h"

extern Game game;

Enemy::Enemy(int health, Vector2f spawnPoint, unique_ptr<MovementPattern>& movementPattern, vector<unique_ptr<Weapon>>& weapons)
	: circle(100.f, 8), health(health), movementPattern(move(movementPattern)), weapons(move(weapons))
{
	circle.setOrigin({ 100.f, 100.f });
	circle.setPosition(spawnPoint);
	circle.setFillColor(Color(128, 0, 0));

	//this->weapons.push_back(make_unique<linearWeapon>(0.1f, 3, 800.f));
	//this->weapons.emplace_back(linearWeapon(0.25f, 3, 600.f));
}

void Enemy::update(float deltaTime, Player& player)
{
	for (auto& weapon : weapons)
		weapon->update(deltaTime, circle.getPosition(), player.getCenter());
}

void Enemy::draw(RenderTarget& target, RenderStates states) const
{
	for (const auto& weapon : weapons)
		target.draw(*weapon, states);
	target.draw(circle, states);
}
