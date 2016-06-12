#include "Tower.h"



Tower::Tower(sf::Texture* _tileset, sf::Vector2i tile, float i, float j, directions dir) :
	Tile(_tileset, tile, i, j, TOWER),
	direction(dir)
{
}


Tower::~Tower()
{
}
