#include "Bullet.h"



Bullet::Bullet(sf::Vector2f _pos, directions _dir)
{
	dir = _dir;
	setSize(sf::Vector2f(6, 6));
	setOrigin(3, 3);
	setFillColor(sf::Color(150,75,0,255));
	switch (dir)
	{
	case UP:
		_pos.y -= 16;
		break;
	case DOWN:
		_pos.y += 16;
		break;
	case LEFT:
		_pos.x -= 16;
		break;
	case RIGHT:
		_pos.x += 16;
		break;
	}
	setPosition(_pos);
}


Bullet::~Bullet()
{
}

void Bullet::move()
{
	switch (dir)
	{
	case UP:
		RectangleShape::move(0, -speed);
		break;
	case DOWN:
		RectangleShape::move(0, speed);
		break;
	case LEFT:
		RectangleShape::move(-speed, 0);
		break;
	case RIGHT:
		RectangleShape::move(speed, 0);
		break;
	}
}
