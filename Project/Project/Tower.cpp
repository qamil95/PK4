#include "Tower.h"



Tower::Tower(sf::Texture* _tileset, sf::Vector2i tile, float i, float j, int _dmg, int _delay, int _ammo, int _hp, directions dir) :
	Tile(_tileset, tile, i, j, TOWER),
	Hitable(_hp),
	direction(dir),
	ammo(_ammo),
	dmg(_dmg),
	delay(_delay),
	counter(_delay)
{
	switch (direction)
	{
	case DOWN:
		changeTexture(sf::Vector2i(7, 13));
		break;
	case LEFT:
		changeTexture(sf::Vector2i(7, 14));
		break;
	case UP:
		changeTexture(sf::Vector2i(7, 12));
		break;
	}
}


Tower::~Tower()
{
}

Bullet* Tower::shoot()
{
	if (counter == 0)
	{
		counter = delay;
		ammo--;
		sf::Vector2f position = getPosition();
		position.x += 16;
		position.y += 16;
		return new Bullet(position, direction, dmg);
	}
	else
	{
		counter--;
		return NULL;
	}
}

void Tower::rotate()
{
	switch (direction)
	{
	case UP:
		direction = RIGHT;
		changeTexture(sf::Vector2i(7,15));
		break;
	case DOWN:
		direction = LEFT;
		changeTexture(sf::Vector2i(7, 14));
		break;
	case LEFT:
		direction = UP;
		changeTexture(sf::Vector2i(7, 12));
		break;
	case RIGHT:
		direction = DOWN; 
		changeTexture(sf::Vector2i(7, 13));
		break;
	}
}