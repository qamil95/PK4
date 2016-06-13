#pragma once
#include "Character.h"
#include "Player.h"

class Enemy :
	public Character
{
private:
	int counter;
public:
	int move_type;
	Enemy(string _type, int _hp, int _dmg, float _movement_speed, float _x, float _y, int mov_type);
	~Enemy();
	void move();
	void move(sf::Vector2f player);
	void attack(Player* player);
};

