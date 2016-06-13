#pragma once

class Hitable
{
protected:
	int HP;
public:
	int maxHP;
	bool dead = false;
	Hitable(int _hp);
	~Hitable();
	void hit(int dmg);
};