#include "Player.h"

Player::Player(string _type, int _hp, float _movement_speed, float _x, float _y) :
	Character(_type, _hp, _movement_speed, _x, _y),
	money(0)
{
	for (int i = 0; i < 4; i++)
		collision[i] = false;
}

Player::~Player()
{
}

void Player::move()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (getPosition().y > 20))
	{
		if (!collision[UP])
			Sprite::move(sf::Vector2f(0, -movement_speed));
		setTextureRect(sf::IntRect(0, 32, 32, 32));
		direction = UP;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && (getPosition().y < 720 - 64))
	{
		if (!collision[DOWN])
			Sprite::move(sf::Vector2f(0, movement_speed));
		setTextureRect(sf::IntRect(32, 32, 32, 32));
		direction = DOWN;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (getPosition().x > 0))
	{
		if(!collision[LEFT])
			Sprite::move(sf::Vector2f(-movement_speed, 0));
		setTextureRect(sf::IntRect(0, 0, 32, 32));
		direction = LEFT;
	}
	if( (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (getPosition().x < 1280))
	{
		if (!collision[RIGHT])
			Sprite::move(sf::Vector2f(movement_speed, 0));
		setTextureRect(sf::IntRect(32, 0, 32, 32));
		direction = RIGHT;
	}
}

string Player::status()
{
	string tmp;
	tmp = "PLAYER INFO:\tHP: ";
	tmp += to_string(hp);
	tmp += "\tMONEY: ";
	tmp += to_string(money);
	return tmp;
}
