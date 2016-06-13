#pragma once
#include "Tile.h"
class Tower :
	public Tile
{
private:
	int ammo, delay, counter;
public:
	int dmg;
	directions direction;
	Tower(sf::Texture* _tileset, sf::Vector2i tile, float i, float j, int _dmg, int _delay, int _ammo, directions dir = RIGHT);
	~Tower();
	bool shoot();
	void rotate();
};

