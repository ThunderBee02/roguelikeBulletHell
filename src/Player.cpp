#include "Player.h"
#include "Game.h"

extern Game game;

Player::Player()
{
	circle.setPointCount(8);
	circle.setRadius(30.f);
	circle.setOrigin({ 30.f, 30.f });
	circle.setPosition({ 600.f, 600.f });
	circle.setFillColor(Color(32, 74, 158));

	weapons.push_back(make_unique<linearWeapon>(0.2f, 3, 500.f));
}

Vector2f Player::getCenter() const
{
	return circle.getPosition();
}

void Player::update(float deltaTime)
{
	//Movement
	Vector2f direction((float)(Keyboard::isKeyPressed(Keyboard::Key::D) - Keyboard::isKeyPressed(Keyboard::Key::A)), (float)(Keyboard::isKeyPressed(Keyboard::Key::S) - Keyboard::isKeyPressed(Keyboard::Key::W)));
	if (float length = direction.length())
		circle.move(direction/length * deltaTime * 400.f);

	//Weapons
	for (auto& weapon : weapons)
	{
		Vector2f direction(0.f, -1.f);
		weapon->update(deltaTime, getCenter(), getCenter() + direction);
	}
}

void Player::draw(RenderTarget& target, RenderStates states) const
{
	for (const auto& weapon : weapons)
	{
		target.draw(*weapon, states);
	}
	target.draw(circle, states);
}
