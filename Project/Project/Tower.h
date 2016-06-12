#pragma once
#include "Tile.h"
class Tower :
	public Tile
{
private:
	directions direction;
public:
	Tower(sf::Texture* _tileset, sf::Vector2i tile, float i, float j, directions dir);
	~Tower();
};

