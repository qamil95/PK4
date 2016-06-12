#include "Tower.h"



Tower::Tower(sf::Texture* _tileset, sf::Vector2i tile, float i, float j, int _dmg, int _delay, directions dir) :
	Tile(_tileset, tile, i, j, TOWER),
	direction(dir),
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
		return true;
	}
	else
	{
		counter--;
		return false;
	}
}
