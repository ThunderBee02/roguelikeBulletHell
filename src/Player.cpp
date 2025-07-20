#include "Player.h"
#include "Game.h"



Player::Player()
{
	circle.setPointCount(5);
	circle.setRadius(30.f);
	circle.setOrigin({ 30.f, 30.f });
	circle.setPosition({ 600.f, 600.f });
	circle.setFillColor(Color(32, 74, 158));

	//weapons.push_back(make_unique<TargetedWeapon>(0.2f, 3, 500.f, game.playerProjectiles, game.enemies));	//turn into directional Weapon
}

void Player::update(float deltaTime)
{
	//Movement
	Vector2f direction((float)(Keyboard::isKeyPressed(Keyboard::Key::D) - Keyboard::isKeyPressed(Keyboard::Key::A)), (float)(Keyboard::isKeyPressed(Keyboard::Key::S) - Keyboard::isKeyPressed(Keyboard::Key::W)));
	if (float length = direction.length())
		circle.move(direction/length * deltaTime * 400.f);

	//Weapons
	for (auto& weapon : weapons)
		weapon->update(deltaTime, getCenter(), getRotation());
}
