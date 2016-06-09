#pragma once
#include "Character.h"

class Enemy :
	public Character
{
private:
	int direction, counter;
public:
	int move_type;
	Enemy(string _type, int _hp, float _movement_speed, float _x, float _y);
	~Enemy();
	void move();
	void move(sf::Vector2f player);
};

