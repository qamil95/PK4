#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Tile.h"
#include "enums.h"

using namespace std;

class Engine
{
private:
	const int window_size_x = 1280;
	const int window_size_y = 720;
	int frame_counter = 0;
	sf::RenderWindow window;
	sf::Text info;
	sf::Font font;
	sf::Clock clock;
	Player* player;
	vector<Enemy*> enemies;	
	Tile* tiles[40][20];
	sf::Texture *tileset;
	sf::Vector2i mouse_tile = { 0,0 };
public:

	Engine();
	~Engine();
	void run();
	void initialize();
	void updateMousePosition();
	void updateCollision(Character* _active, sf::Sprite* _reference, float _range = 0);
	void createEnemies(int number);
	void refresh();
	string status();
};

