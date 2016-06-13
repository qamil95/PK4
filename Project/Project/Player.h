#pragma once
#include "Character.h"

class Player :
	public Character
{
public:
	int money, ammo;
	Player(string _type, int _hp, float _movement_speed, float _x, float _y);
	~Player();
	void move();
	string status();
};

