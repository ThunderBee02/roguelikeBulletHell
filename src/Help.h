#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class FloatCircle
{
public:
	Vector2f center;
	float radius;

	FloatCircle(Vector2f center, float radius);
	
	bool intersects(const FloatCircle& circle) const;
	bool intersects(const CircleShape& circle) const;
};
