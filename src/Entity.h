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

public:
	int health;
	int damage;

	Entity(int health, int damage);

	void move(Vector2f offset, Angle angle);

	Vector2f getCenter() const;
	Angle getRotation() const;
	bool isOutside() const;
	bool doDamage(vector<unique_ptr<Entity>>& targets) const;

	virtual bool update(float deltaTime) = 0;
	virtual bool takeDamage(int damage);
	virtual bool checkCollision(const Entity& other) const;

	virtual void draw(RenderTarget& target, RenderStates states) const override;
};