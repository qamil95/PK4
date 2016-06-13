#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <list>
#include "Bullet.h"
#include "Character.h"
#include "Enemy.h"
#include "enums.h"
#include "Hitable.h"
#include "Player.h"
#include "Tile.h"
#include "Tower.h"


using namespace std;

class Engine
{
private:
	const int window_size_x = 1280;
	const int window_size_y = 720;
	int frame_counter = 0;
	bool pause = false;
	sf::RenderWindow window;
	sf::Text stat, info;
	sf::Font font;
	sf::Clock clock;
	sf::Time timer;
	Player* player;
	vector<Enemy*> enemies;	
	list<Bullet*> bullets;
	Tile* tiles[40][20];
	sf::Texture *tileset;
	sf::Vector2i mouse_tile = { 0,0 };
	string msg = "Wiadomosci: w czasie pauzy mozna wszystko poza chodzeniem i strzelaniem!";
public:
	Engine(int trees);
	~Engine();
	void run();
	void updateMousePosition();
	void updateCollision(Character* _active, sf::Sprite* _reference, float _range = 0);
	void createEnemies(int number);
	void createTower(sf::Vector2i pos);
	void deleteTower(sf::Vector2i pos);
	void refresh();
	string status();
	void sendMsg(string _msg);
};

