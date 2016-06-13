#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "enums.h"
#include "Hitable.h"

using namespace std;

class Character :
	public sf::Sprite,
	public Hitable
{
private:
	sf::Texture *texture;
protected:	
	float movement_speed;
public:
	bool collision[4];
	directions direction;
	Character(string _type, int _hp, float _movement_speed, float _x, float _y);
	sf::Vector2i getPositionTile();
	float getMovementSpeed();
	int getHP();
	virtual ~Character();
	virtual void move() = 0;
};

