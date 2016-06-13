#pragma once
#include "Character.h"
#include "Bullet.h"

class Player :
	public Character
{
private:
	int money, points, ammo;
public:	
	int delay = 0, shoot_delay = 30;
	Player(string _type, int _hp, int _dmg, float _movement_speed, float _x, float _y);
	~Player();
	void move();
	bool increaseShootSpeed();
	bool increaseDMG();
	bool changeMoney(int _money, int _points = 0);
	bool buyAmmo();
	int getPoints();
	string status();
	Bullet* shoot();
};

