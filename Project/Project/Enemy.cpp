#include "Enemy.h"

Enemy::Enemy(string _type, int _hp, int _dmg, float _movement_speed, float _x, float _y, int mov_type) :
	counter(0),
	move_type(mov_type),
	Character(_type, _hp, _dmg, _movement_speed, _x, _y) 
{
}

Enemy::~Enemy()
{
}

void Enemy::move() //AI losowe
{
	if (counter == 60)
	{
		counter = 0;
		direction = static_cast<directions>(rand() % 4);
	}
	switch (direction)
	{
	case UP:
		if ((getPosition().y > 0) && !collision[UP])
			Sprite::move(0, -movement_speed);
		setTextureRect(sf::IntRect(0, 32, 32, 32));
		break;
	case DOWN:
		if ((getPosition().y < 720) && !collision[DOWN])
			Sprite::move(0, movement_speed);
		setTextureRect(sf::IntRect(32, 32, 32, 32));
		break;
	case LEFT:
		if ((getPosition().x > 0) && !collision[LEFT])
			Sprite::move(-movement_speed, 0);
		setTextureRect(sf::IntRect(0, 0, 32, 32));
		break;
	case RIGHT:
		if ((getPosition().x < 1280) && !collision[RIGHT])
			Sprite::move(movement_speed, 0);
		setTextureRect(sf::IntRect(32, 0, 32, 32));
		break;
	}
	counter++;
}

void Enemy::move(sf::Vector2f _player) //AI goniace gracza
{
	if (getPosition().x > _player.x)
	{
		setTextureRect(sf::IntRect(0, 0, 32, 32));
		direction = LEFT;
		if (!collision[LEFT])
		{
			Sprite::move(-movement_speed, 0);
			while (getPosition().x < _player.x)
				Sprite::move(1, 0);
		}			
	}		
	else if (getPosition().x < _player.x)
	{
		setTextureRect(sf::IntRect(32, 0, 32, 32));
		direction = RIGHT;
		if (!collision[RIGHT])
		{
			Sprite::move(movement_speed, 0);
			while (getPosition().x > _player.x)
				Sprite::move(-1, 0);
		}			
	}		

	if (getPosition().y > _player.y)
	{
		setTextureRect(sf::IntRect(0, 32, 32, 32));
		direction = UP;
		if (!collision[UP])
		{
			Sprite::move(0, -movement_speed);
			while (getPosition().y < _player.y)
				Sprite::move(0, 1);
		}
	}
	else if (getPosition().y < _player.y)
	{
		setTextureRect(sf::IntRect(32, 32, 32, 32));
		direction = DOWN;
		if (!collision[DOWN])
		{
			Sprite::move(0, movement_speed);
			while (getPosition().y > _player.y)
				Sprite::move(0, -1);
		}
	}

	if (counter == 60)
		counter = 0;
	else
		counter++;		
}

void Enemy::attack(Player * player)
{
	sf::RectangleShape hitbox = sf::RectangleShape(sf::Vector2f(48, 48));
	hitbox.setOrigin(24, 24);
	hitbox.setPosition(getPosition());
	sf::FloatRect pla = player->getGlobalBounds();
	switch (direction)
	{
	case UP:
		hitbox.move(0, -32);
		break;
	case DOWN:
		hitbox.move(0, 32);
		break;
	case LEFT:
		hitbox.move(-32, 0);
		break;
	case RIGHT:
		hitbox.move(32, 0);
		break;
	}
	if ((hitbox.getGlobalBounds().intersects(pla)) && 
		((counter==0) || 
		((move_type == 1) && (counter%15 == 0))))
	{
		player->hit(dmg);
		player->setColor(sf::Color::Red);
	}		
}
