#pragma once
#include "Help.h"
#include "Player.h"
#include "Enemy.h"

class Game : public Drawable
{
private:
	
public:
	static inline vector<unique_ptr<Entity>> players;
	static inline vector<unique_ptr<Entity>> enemies;
	static inline vector<unique_ptr<Entity>> playerProjectiles;
	static inline vector<unique_ptr<Entity>> enemyProjectiles;

	Game();

	void update(float deltaTime);

	virtual void draw(RenderTarget& target, RenderStates states) const override;
};
