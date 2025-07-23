#pragma once
#include "Help.h"
#include "Entity.h"

struct EntityPool
{
	vector<unique_ptr<Entity>> characters;
	vector<unique_ptr<Entity>> generalProjectiles;
	vector<unique_ptr<Entity>> destroyableProjectiles;
	//Laser
	//selfShield
	array<vector<unique_ptr<Entity>>*, 3 > all = { &characters, &generalProjectiles, &destroyableProjectiles };

	void update(float deltaTime);
	void cullProjectiles();
	void draw(RenderTarget& target, RenderStates& states) const;
};

class Game : public Drawable
{
private:
	
public:
	static inline EntityPool playerEntities;
	static inline EntityPool enemyEntities;

	Game();

	void update(float deltaTime);

	virtual void draw(RenderTarget& target, RenderStates states) const override;
};
