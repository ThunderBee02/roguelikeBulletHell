#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

void EntityPool::update(float deltaTime)
{
	/*for (auto entityVector : all)
		for (unique_ptr<Entity>& entity : *entityVector)
			entity->update(deltaTime);*/
	for (auto entityVector : all)
	{
		entityVector->erase(remove_if(entityVector->begin(), entityVector->end(),
			[&](unique_ptr<Entity>& projectile) {
				return projectile->update(deltaTime);
			}), entityVector->end());
	}
}

void EntityPool::cullProjectiles()
{
	for (auto entityVector : all)
	{
		entityVector->erase(remove_if(entityVector->begin(), entityVector->end(),
			[](unique_ptr<Entity>& projectile) {
				return projectile->isOutside();
			}), entityVector->end());
	}
}

void EntityPool::draw(RenderTarget& target, RenderStates& states) const
{
	for (const unique_ptr<Entity>& self : characters)
		target.draw(*self, states);
	for (const unique_ptr<Entity>& projectile : generalProjectiles)
		target.draw(*projectile, states);
	for (const unique_ptr<Entity>& projectile : destroyableProjectiles)
		target.draw(*projectile, states);
}

/*****************************************************************************************************************/

Game::Game()
{
	playerEntities.characters.push_back(make_unique<Player>());

	vector<unique_ptr<Weapon>> weapons;
	unique_ptr<MovementPattern> movePat;
	enemyEntities.characters.push_back(make_unique<Enemy>(10, Vector2f(100.f, 100.f), movePat, weapons));
}

void Game::update(float deltaTime)
{
	playerEntities.update(deltaTime);
	enemyEntities.update(deltaTime);

	playerEntities.cullProjectiles();
	enemyEntities.cullProjectiles();
}

void Game::draw(RenderTarget& target, RenderStates states) const
{
	playerEntities.draw(target, states);
	enemyEntities.draw(target, states);
}
