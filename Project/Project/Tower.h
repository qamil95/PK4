#pragma once
#include "Tile.h"
#include "Hitable.h"

class Tower :
	public Tile,
	public Hitable
{
private:
	int delay, counter;
public:
	bool dead = false;
	int dmg, hp, ammo;
	directions direction;
	Tower(sf::Texture* _tileset, sf::Vector2i tile, float i, float j, int _dmg, int _delay, int _ammo, int _hp, directions dir = RIGHT);
	~Tower();
	bool shoot();
	void rotate();
	void hit(int dmg);
};

