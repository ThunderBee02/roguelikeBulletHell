#pragma once
#include "Help.h"

class FloatCircle
{
public:
	Vector2f center;
	float radius;

	FloatCircle(Vector2f center, float radius);

	bool intersects(const FloatCircle& other) const;
	bool intersects(Vector2f offset, const FloatCircle& other, Vector2f otherOffset) const;
};

class Entity : public Drawable
{
protected:
	Texture texture;
	CircleShape circle;
	vector<FloatCircle> hitbox;

	bool checkCollision(const Entity& other) const;

public:
	Vector2f getCenter() const;
	Angle getRotation() const;

	void move(Vector2f offset, Angle angle);

	bool isOutside() const;
	virtual void update(float deltaTime) = 0;

	virtual void draw(RenderTarget& target, RenderStates states) const override;
};