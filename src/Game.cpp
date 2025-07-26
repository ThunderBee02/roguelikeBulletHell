#include "Game.h"
#include "Player.h"
#include "Enemy.h"

Game::Game()
{
	playerEntities.characters.push_back(make_unique<Player>());

	vector<unique_ptr<Weapon>> weapons;
	unique_ptr<MovementPattern> movePat;
	enemyEntities.characters.push_back(make_unique<Enemy>(10, Vector2f(100.f, 100.f), movePat, weapons));
}

void Game::update(float deltaTime)
{
	for (auto entityVector : playerEntities.all)
		entityVector->erase(remove_if(entityVector->begin(), entityVector->end(),
			[&](unique_ptr<Entity>& entity) {
				return entity->update(deltaTime);
			}), entityVector->end());
	for (auto entityVector : enemyEntities.all)
		entityVector->erase(remove_if(entityVector->begin(), entityVector->end(),
			[&](unique_ptr<Entity>& entity) {
				return entity->update(deltaTime);
			}), entityVector->end());
}

void Game::draw(RenderTarget& target, RenderStates states) const
{
	for (vector<unique_ptr<Entity>>* entityVector : playerEntities.all)
		for (const unique_ptr<Entity>& entity : *entityVector)
			target.draw(*entity, states);
	for (vector<unique_ptr<Entity>>* entityVector : enemyEntities.all)
		for (const unique_ptr<Entity>& entity : *entityVector)
			target.draw(*entity, states);
}
