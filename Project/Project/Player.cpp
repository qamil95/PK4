#include "Player.h"

Player::Player(string _type, int _hp, float _movement_speed, float _x, float _y) :
	Character(_type, _hp, _movement_speed, _x, _y) 
{
	for (int i = 0; i < 4; i++)
		collision[i] = false;
}

Player::~Player()
{
}

void Player::move(directions dir)
{
	switch (dir)
	{
	case UP:
		if ((getPosition().y > 20) && !collision[UP])
			Sprite::move(sf::Vector2f(0, -movement_speed));
		setTextureRect(sf::IntRect(0, 32, 32, 32));
		break;
	case DOWN:
		if ((getPosition().y < 720-64) && !collision[DOWN])
			Sprite::move(sf::Vector2f(0, movement_speed));
		setTextureRect(sf::IntRect(32, 32, 32, 32));
		break;
	case LEFT:
		if ((getPosition().x > 0) && !collision[LEFT])
			Sprite::move(sf::Vector2f(-movement_speed, 0));
		setTextureRect(sf::IntRect(0, 0, 32, 32));
		break;
	case RIGHT:
		if ((getPosition().x < 1280) && !collision[RIGHT])
			Sprite::move(sf::Vector2f(movement_speed, 0));
		setTextureRect(sf::IntRect(32, 0, 32, 32));
		break;

	}
}