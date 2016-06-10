#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"

class Bullet :
	public sf::RectangleShape
{
private:
	directions dir;
	float speed = 10;
public:
	Bullet(sf::Vector2f _pos, directions _dir);
	~Bullet();
	void move();
};

