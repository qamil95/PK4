#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"

class Bullet :
	public sf::RectangleShape
{
private:
	directions dir;
	float speed = 25;
public:
	Bullet(sf::Vector2f _pos, directions _dir, int _dmg);
	~Bullet();
	void move();
	int dmg;
	bool destroy = false;
};

