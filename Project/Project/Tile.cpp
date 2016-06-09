#include "Tile.h"


Tile::Tile(sf::Texture* _tileset, sf::Vector2i tile, float i, float j, tileType _tileType) :
	tType(_tileType)
{
	setTexture(*_tileset);
	setTextureRect(sf::IntRect(32*tile.x, 32*tile.y, 32, 32));
	setOrigin(0,0);
	setPosition(32*i,32*j+20);
}

Tile::~Tile()
{
}

void Tile::changeTexture(sf::Vector2i tile)
{
	setTextureRect(sf::IntRect(32 * tile.x, 32 * tile.y, 32, 32));
}
