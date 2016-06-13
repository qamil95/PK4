#pragma once

class Hitable
{
protected:
	int hp;
public:
	bool dead = false;
	Hitable(int _hp);
	~Hitable();
	void hit(int dmg);
};

