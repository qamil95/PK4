#include "Player.h"

Player::Player(string _type, int _hp, float _movement_speed, float _x, float _y) :
	Character(_type, _hp, _movement_speed, _x, _y),
	money(0),
	ammo(50)
{
	for (int i = 0; i < 4; i++)
		collision[i] = false;
}

Player::~Player()
{
}

void Player::move()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (getPosition().y > 20))
	{
		if (!collision[UP])
			Sprite::move(sf::Vector2f(0, -movement_speed));
		setTextureRect(sf::IntRect(0, 32, 32, 32));
		direction = UP;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && (getPosition().y < 720 - 64))
	{
		if (!collision[DOWN])
			Sprite::move(sf::Vector2f(0, movement_speed));
		setTextureRect(sf::IntRect(32, 32, 32, 32));
		direction = DOWN;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (getPosition().x > 0))
	{
		if(!collision[LEFT])
			Sprite::move(sf::Vector2f(-movement_speed, 0));
		setTextureRect(sf::IntRect(0, 0, 32, 32));
		direction = LEFT;
	}
	if( (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (getPosition().x < 1280))
	{
		if (!collision[RIGHT])
			Sprite::move(sf::Vector2f(movement_speed, 0));
		setTextureRect(sf::IntRect(32, 0, 32, 32));
		direction = RIGHT;
	}
}

bool Player::increaseShootSpeed()
{
	if ((shoot_delay > 2) && (changeMoney(-100)))
	{
		shoot_delay--;
		return true;
	}		
	else
		return false;
}

bool Player::increaseDMG()
{
	if (changeMoney(-150))
	{
		dmg++;
		return true;
	}		
	else
		return false;
}

bool Player::changeMoney(int _money, int _points)
{
	if (money + _money > 0)
	{
		money += _money;
		points += _points;
		return true;
	}
	else
		return false;
}

bool Player::buyAmmo()
{
	if (money > 500)
	{
		money -= 100;
		ammo += 1000;
		return true;
	}
	else if (money > 50)
	{
		money-= 10;
		ammo += 100;
		return true;
	}
	else if (money > 0)
	{
		money--;
		ammo += 10;
		return true;
	}
	else
		return false;
}

string Player::status()
{
	string tmp;
	tmp = "PLAYER INFO:\tHP: ";
	tmp += to_string(HP);
	tmp += "\tAMMO: ";
	tmp += to_string(ammo);
	tmp += "\tDMG: ";
	tmp += to_string(dmg);
	tmp += "\tShootsPerSecond: ";
	tmp += to_string((float)60/shoot_delay);
	tmp += "\tMONEY: ";
	tmp += to_string(money);
	tmp += "\tPOINTS: ";
	tmp += to_string(points);
	return tmp;
}

Bullet * Player::shoot()
{
	if ((ammo > 0) && (delay < 0)) //moze strzelic
	{
		ammo--;
		sf::Vector2f position = getPosition();
		delay = shoot_delay;
		return new Bullet(position, direction, dmg);
	}
	else
		return NULL;
}
