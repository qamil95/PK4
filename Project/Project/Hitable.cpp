#include "Hitable.h"



Hitable::Hitable(int _hp):
	hp(_hp)
{
}


Hitable::~Hitable()
{
}

void Hitable::hit(int dmg)
{
	hp -= dmg;
	if (hp <= 0)
		dead = true;
}
