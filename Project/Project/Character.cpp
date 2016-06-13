#include "Character.h"

Character::Character(string _type, int _hp, float _movement_speed, float _x, float _y) :
	hp(_hp),
	movement_speed(_movement_speed),
	direction(UP)
{
	string name;
	name = "files/";
	name += _type;
	name += ".png";
	texture = new(sf::Texture);
	texture->loadFromFile(name);
	setTexture(*texture);
	setTextureRect(sf::IntRect(0, 32, 32, 32));
	setOrigin(sf::Vector2f(16, 16));
	setPosition(_x, _y);
}

sf::Vector2i Character::getPositionTile()
{
	float x, y;
	x = getPosition().x;
	y = getPosition().y -20;
	x = x / 32;
	y = y / 32;
	return sf::Vector2i((int)x, (int)y);
}

float Character::getMovementSpeed()
{
	return movement_speed;
}

int Character::getHP()
{
	return hp;
}


Character::~Character()
{
	delete texture;
}

void Character::hit(int dmg)
{
	hp -= dmg;
	if (hp <= 0)
		dead = true;
	setColor(sf::Color(255, 0, 0, 180));
}
