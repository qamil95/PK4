#pragma once
#include "Tile.h"
class Tower :
	public Tile
{
private:
	int delay, counter;
public:
	int dmg, hp, ammo;
	directions direction;
	Tower(sf::Texture* _tileset, sf::Vector2i tile, float i, float j, int _dmg, int _delay, int _ammo, int _hp, directions dir = RIGHT);
	~Tower();
	bool shoot();
	void rotate();
	void hit(int dmg);
};

