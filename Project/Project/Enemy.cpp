#include "Enemy.h"

Enemy::Enemy(string _type, int _hp, float _movement_speed, float _x, float _y) :
	counter(0),
	Character(_type, _hp, _movement_speed, _x, _y) 
{
	move_type = rand() % 2;
}

Enemy::~Enemy()
{
}

void Enemy::move() //AI losowe
{
	if (counter == 60)
	{
		counter = 0;
		direction = static_cast<directions>(rand() % 4);
	}
	switch (direction)
	{
	case 0:
		if ((getPosition().x > 0) && !collision[LEFT])
			Sprite::move(-movement_speed, 0);
		setTextureRect(sf::IntRect(0, 0, 32, 32));
		break;
	case 1:
		if ((getPosition().x < 1280) && !collision[RIGHT])
			Sprite::move(movement_speed, 0);
		setTextureRect(sf::IntRect(32, 0, 32, 32));
		break;
	case 2:
		if ((getPosition().y > 0) && !collision[UP])
			Sprite::move(0, -movement_speed);
		setTextureRect(sf::IntRect(0, 32, 32, 32));
		break;
	case 3:
		if ((getPosition().y < 720) && !collision[DOWN])
			Sprite::move(0, movement_speed);
		setTextureRect(sf::IntRect(32, 32, 32, 32));
		break;
	}
	counter++;
}

void Enemy::move(sf::Vector2f _player) //AI goniace gracza
{
	if ((getPosition().x > _player.x) && !collision[LEFT])
	{
		Sprite::move(-movement_speed, 0);
		setTextureRect(sf::IntRect(0, 0, 32, 32));
		direction = LEFT;
		while (getPosition().x < _player.x)
			Sprite::move(1, 0);
	}		
	else if ((getPosition().x < _player.x) && !collision[RIGHT])
	{
		Sprite::move(movement_speed, 0);
		setTextureRect(sf::IntRect(32, 0, 32, 32));
		direction = RIGHT;
		while (getPosition().x > _player.x)
			Sprite::move(-1, 0);
	}		

	if ((getPosition().y > _player.y) && !collision[UP])
	{
		Sprite::move(0, -movement_speed);
		setTextureRect(sf::IntRect(0, 32, 32, 32));
		direction = UP;
		while (getPosition().y < _player.y)
			Sprite::move(0, 1);
	}
	else if ((getPosition().y < _player.y) && !collision[DOWN])
	{
		Sprite::move(0, movement_speed);
		setTextureRect(sf::IntRect(32, 32, 32, 32));
		direction = DOWN;
		while (getPosition().y > _player.y)
			Sprite::move(0, -1);
	}
		
}
