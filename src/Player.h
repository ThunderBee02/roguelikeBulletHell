#pragma once
#include "Help.h"
#include "Weapon.h"

class Player : public Drawable
{
private:
	Texture texture;
	CircleShape circle;

	vector<unique_ptr<Weapon>> weapons;

public:
	Player();

	Vector2f getCenter() const;

	void update(float deltaTime);

	virtual void draw(RenderTarget& target, RenderStates states) const override;
};
