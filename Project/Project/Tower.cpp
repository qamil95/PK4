#include "Tower.h"



Tower::Tower(sf::Texture* _tileset, sf::Vector2i tile, float i, float j, int _dmg, int _delay, int _ammo, directions dir) :
	Tile(_tileset, tile, i, j, TOWER),
	direction(dir),
	ammo(_ammo),
	dmg(_dmg),
	delay(_delay),
	counter(_delay)
{
}


Tower::~Tower()
{
}

bool Tower::shoot()
{
	if (counter == 0)
	{
		counter = delay;
		ammo--;
		return true;
	}
	else
	{
		counter--;
		return false;
	}
}

void Tower::rotate()
{
	switch (direction)
	{
	case UP:
		direction = RIGHT;
		break;
	case DOWN:
		direction = LEFT;
		break;
	case LEFT:
		direction = UP;
		break;
	case RIGHT:
		direction = DOWN;
		break;
	}
}
