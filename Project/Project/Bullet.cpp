#include "Bullet.h"



Bullet::Bullet(sf::Vector2f _pos, directions _dir, int _dmg) :
	dir(_dir),
	dmg(_dmg)
{
	setSize(sf::Vector2f(8, 8));
	setOrigin(4, 4);
	setFillColor(sf::Color(192,192,192,200));
	setOutlineColor(sf::Color(0,0,0,100));
	setOutlineThickness(1);
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
