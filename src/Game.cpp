#include "Game.h"

Game::Game()
{
	vector<unique_ptr<Weapon>> weapons;
	unique_ptr<MovementPattern> movePat;
	enemies.emplace_back(10, Vector2f(100.f, 100.f), movePat, weapons);
}

void Game::update(float deltaTime)
{
	for (Enemy& enemy : enemies)
		enemy.update(deltaTime, player);
	player.update(deltaTime);
}

void Game::draw(RenderTarget& target, RenderStates states) const
{
	for (const Enemy& enemy : enemies)
		target.draw(enemy, states);
	target.draw(player, states);
}
