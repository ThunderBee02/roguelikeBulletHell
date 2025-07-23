#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

template <typename T>
inline void clamp(T& var, const T& limit)
{
	if (var > limit)
		var = limit;
	else if (var < -limit)
		var = -limit;
}
