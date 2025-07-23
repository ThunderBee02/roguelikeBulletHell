#include "Player.h"
#include "Game.h"

Player::Player()
	: Entity(5, 1)
{
	circle.setPointCount(5);
	circle.setRadius(30.f);
	circle.setOrigin({ 30.f, 30.f });
	circle.setPosition({ 600.f, 600.f });
	circle.setFillColor(Color(32, 74, 158));

	hitbox.emplace_back(Vector2f(0.f, 0.f), 30.f);

	weapons.push_back(make_unique<TargetedWeapon>(1, 0.5f, 400.f, Vector2f(0.f, -50.f), Game::playerEntities, Game::enemyEntities));	//turn into directional Weapon
}

bool Player::update(float deltaTime)
{
	//Movement
	Vector2f direction((float)(Keyboard::isKeyPressed(Keyboard::Key::D) - Keyboard::isKeyPressed(Keyboard::Key::A)), (float)(Keyboard::isKeyPressed(Keyboard::Key::S) - Keyboard::isKeyPressed(Keyboard::Key::W)));
	if (float length = direction.length())
		circle.move(direction/length * deltaTime * 400.f);

	//Weapons
	for (auto& weapon : weapons)
		weapon->update(deltaTime, getCenter(), getRotation());

	return 0;
}
