#include "Game.h"

Game::Game()
{
	players.push_back(make_unique<Player>());

	vector<unique_ptr<Weapon>> weapons;
	unique_ptr<MovementPattern> movePat;
	enemies.push_back(make_unique<Enemy>(10, Vector2f(100.f, 100.f), movePat, weapons));
}

void Game::update(float deltaTime)
{
	for (unique_ptr<Entity>& enemy : enemies)
		enemy->update(deltaTime);
	for (unique_ptr<Entity>& player : players)
		player->update(deltaTime);
	for (unique_ptr<Entity>& projectile : enemyProjectiles)
		projectile->update(deltaTime);
	for (unique_ptr<Entity>& projectile : playerProjectiles)
		projectile->update(deltaTime);

	playerProjectiles.erase(remove_if(playerProjectiles.begin(), playerProjectiles.end(),
		[](unique_ptr<Entity>& projectile) {
			return projectile->isOutside();
		}), playerProjectiles.end());
	enemyProjectiles.erase(remove_if(enemyProjectiles.begin(), enemyProjectiles.end(),
		[](unique_ptr<Entity>& projectile) {
			return projectile->isOutside();
		}), enemyProjectiles.end());
}

void Game::draw(RenderTarget& target, RenderStates states) const
{
	for (const unique_ptr<Entity>& enemy : enemies)
		target.draw(*enemy, states);
	for (const unique_ptr<Entity>& player : players)
		target.draw(*player, states);
	for (const unique_ptr<Entity>& projectile : playerProjectiles)
		target.draw(*projectile, states);
	for (const unique_ptr<Entity>& projectile : enemyProjectiles)
		target.draw(*projectile, states);
}
