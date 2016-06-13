#include "Hitable.h"

Hitable::Hitable(int _hp):
	HP(_hp),
	maxHP(_hp)
{
}

Hitable::~Hitable()
{
}

void Hitable::hit(int dmg)
{
	HP -= dmg;
	if (HP <= 0)
		dead = true;
}
