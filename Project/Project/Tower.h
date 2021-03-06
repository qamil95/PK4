#pragma once
#include "Tile.h"
#include "Hitable.h"
#include "Bullet.h"

class Tower :
	public Tile,
	public Hitable
{
private:
	int delay, counter;
public:
	int dmg, ammo;
	directions direction;
	Tower(sf::Texture* _tileset, sf::Vector2i tile, float i, float j, int _dmg, int _delay, int _ammo, int _hp, directions dir = RIGHT);
	~Tower();
	Bullet* shoot();
	void rotate();
};

