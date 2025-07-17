#pragma once
#include "Help.h"

class Projectile : public Drawable
{
private:
	Texture texture;
	CircleShape circle;

public:
	Vector2f direction;

	Projectile(float radius, Vector2f position, Vector2f direction);

	bool cull() const;

	void move(Vector2f offset);

	virtual void draw(RenderTarget& target, RenderStates states) const override;
};