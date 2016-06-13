#pragma once
#include "Character.h"
#include "Bullet.h"

class Player :
	public Character
{
private:
	int money, points, ammo, dmg=10;
public:	
	Player(string _type, int _hp, float _movement_speed, float _x, float _y);
	~Player();
	void move();
	bool changeMoney(int _money, int _points = 0);
	bool buyAmmo();
	string status();
	Bullet* shoot();
};

