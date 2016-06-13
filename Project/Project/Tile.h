#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "enums.h"

using namespace std;

class Tile :
	public sf::Sprite
{
public:	
	tileType tType;
	Tile(sf::Texture* _tileset, sf::Vector2i tile, float i, float j, tileType _tileType);
	~Tile();
	void changeTexture(sf::Vector2i tile);
};

