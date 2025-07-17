#pragma once
#include "Help.h"
#include "Player.h"
#include "Enemy.h"

class Game : public Drawable
{
private:
	
public:
	Player player;
	vector<Enemy> enemies;

	Game();

	void update(float deltaTime);

	virtual void draw(RenderTarget& target, RenderStates states) const override;
};
