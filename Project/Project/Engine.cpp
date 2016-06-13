#include "Engine.h"

Engine::Engine(int trees)
{
	srand((unsigned int)time(NULL));

	window.create(sf::VideoMode(window_size_x, window_size_y), "Projekt PK4", sf::Style::Close);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	font.loadFromFile("files/arial.ttf");
	stat.setFont(font);
	stat.setCharacterSize(16);
	stat.setColor(sf::Color::White);
	stat.setPosition(sf::Vector2f(0, 0));

	info.setFont(font);
	info.setCharacterSize(14);
	info.setColor(sf::Color::White);
	info.setPosition(sf::Vector2f(6, 32 * 20 + 26));
	info.setString("TESTOWY NAPISIK Z INFORMACJAMI\nLN2\nLN3");

	//Open tileset
	tileset = new (sf::Texture);
	tileset->loadFromFile("files/tileset.png");

	//create map
	for (int i = 0; i<40; i++)
		for (int j = 0; j < 20; j++)
		{
			if ((i == 0) || (i == 39) || (j == 0) || (j == 19))
				tiles[i][j] = new Tile(tileset, sf::Vector2i(10, 0), (float)i, (float)j, WALL);
			else
				tiles[i][j] = new Tile(tileset, sf::Vector2i(0, 0), (float)i, (float)j, GRASS);
		}

	//add trees
	for (int i = 0; i < trees; i++)
	{
		int x = rand() % 40;
		int y = rand() % 20;
		if (tiles[x][y]->tType == GRASS)
		{
			tiles[x][y]->changeTexture(sf::Vector2i(5, 19)); 
			tiles[x][y]->tType = WALL;
		}
	}

	//player and enemies
	player = new Player("player", 100, 4, (float)window.getSize().x / 2, (float)window.getSize().y / 2);
	createEnemies(4);
}

Engine::~Engine()
{
}

void Engine::run()
{		
	while (window.isOpen()) //main loop
	{
		sf::Event event;
		updateMousePosition();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Pause))
				if (pause)
					pause = false;
				else
					pause = true;
			if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
			{
				if (Tower* tmp = dynamic_cast<Tower*>(tiles[mouse_tile.x][mouse_tile.y]))
					tmp->rotate();
				else if (tiles[mouse_tile.x][mouse_tile.y]->tType == GRASS)
					createTower(sf::Vector2i(mouse_tile.x, mouse_tile.y));
			}
			if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Right) && (tiles[mouse_tile.x][mouse_tile.y]->tType == TOWER))
				deleteTower(sf::Vector2i(mouse_tile.x, mouse_tile.y));
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Add))
				createEnemies(1);
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Subtract) && enemies.size() != 0)
			{
				delete enemies.back();
				enemies.pop_back();
			}				
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Delete))
				cout << "BREAKPOINT" <<endl;			
		}

		if (!pause)
		{
			//SPRAWDZANIE KOLIZJI I RUCH
			for (vector<Enemy*>::iterator act = enemies.begin(); act != enemies.end(); ++act)
			{
				for (int i = 0; i < 4; i++)
					(*act)->collision[i] = false; //reset kolizji

				updateCollision((*act), player, 8); //z graczem

				for (vector<Enemy*>::iterator ref = enemies.begin(); ref != enemies.end(); ++ref)
					if (ref != act)
						updateCollision((*act), (*ref)); //z innymi przeciwnikami

				for (int i = 0; i<40; i++) //ze scianami
					for (int j = 0; j < 20; j++)
						updateCollision((*act), tiles[i][j]);

				if ((*act)->move_type == 0) //ruch przeciwnikow
					(*act)->move(player->getPosition());
				else
					(*act)->move();
			}

			for (int i = 0; i < 4; i++)
				player->collision[i] = false; //reset kolizji gracza

			for (vector<Enemy*>::iterator ref = enemies.begin(); ref != enemies.end(); ++ref)
				updateCollision(player, (*ref), 8); //z przeciwnikami

			for (int i = 0; i < 40; i++) //ze scianami
				for (int j = 0; j < 20; j++)
					updateCollision(player, tiles[i][j]);
			player->move();
			//END SPR KOL I RUCH


			//przeliczenie pozycji pociskow
			for (list<Bullet*>::iterator act = bullets.begin(); act != bullets.end(); ++act)
			{
				(*act)->move();
				sf::FloatRect tmp = (*act)->getGlobalBounds();
				if (tmp.intersects(player->getGlobalBounds()))
				{
					(*act)->destroy = true;
					player->hit((*act)->dmg);
				}

				for (vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
					if (tmp.intersects((*it)->getGlobalBounds()))
					{
						(*act)->destroy = true;
						(*it)->hit((*act)->dmg);
					}

				for (int i = 0; i < 40; i++)
					for (int j = 0; j < 20; j++)
						if ((tiles[i][j]->tType != GRASS) &&
							(tmp.intersects(tiles[i][j]->getGlobalBounds())))
						{
							(*act)->destroy = true;
							if (Tower* tmp = dynamic_cast<Tower*>(tiles[i][j]))
								tmp->hit((*act)->dmg);
						}
							
				if ((*act)->destroy)
				{
					(*act)->setFillColor(sf::Color::Red); // zamienic to na info o zadanym dmg
					(*act)->setSize(sf::Vector2f(20, 20));
					(*act)->setOrigin(10, 10);
				}

			}


			//TYMCZASOWE STRZA£Y
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				bullets.push_back(new Bullet(player->getPosition(), player->direction, 10));

			for (int i = 0; i < 40; i++)
				for (int j = 0; j < 20; j++)
					if (Tower * tmp = dynamic_cast<Tower*>(tiles[i][j]))
						if (tmp->shoot())
						{
							sf::Vector2f position = tmp->getPosition();
							position.x += 16;
							position.y += 16;
							bullets.push_back(new Bullet(position, tmp->direction, tmp->dmg));
						}
		}
				

		stat.setString(status());
		//cout << (std::string)stat.getString() << endl;
		refresh();
		frame_counter++;
	}
}

void Engine::updateMousePosition()
{
	if ((sf::Mouse::getPosition(window).x < window_size_x) && (sf::Mouse::getPosition(window).y < window_size_y - 64) && (sf::Mouse::getPosition(window).x > 0) && (sf::Mouse::getPosition(window).y > 20))
	{
		tiles[mouse_tile.x][mouse_tile.y]->setColor(sf::Color::White);
		mouse_tile.x = sf::Mouse::getPosition(window).x / 32;
		mouse_tile.y = (sf::Mouse::getPosition(window).y - 20) / 32;
		tiles[mouse_tile.x][mouse_tile.y]->setColor(sf::Color(255, 255, 255, 200));
	}
	else
	{
		tiles[mouse_tile.x][mouse_tile.y]->setColor(sf::Color::White);
		mouse_tile.x = 0;
		mouse_tile.y = 0;
	}
}

void Engine::updateCollision(Character* _active, sf::Sprite * _reference, float _range)
{
	Tile* tmp;
	if ((tmp = dynamic_cast<Tile*>(_reference)) && (tmp->tType == GRASS))
		return;

	sf::FloatRect act = _active->getGlobalBounds();
	act.top -= _active->getMovementSpeed() + _range;
	if (act.intersects(_reference->getGlobalBounds()))
		_active->collision[UP] = true;
	act.top += _active->getMovementSpeed() + _range;
	act.height += _active->getMovementSpeed() + _range;
	if (act.intersects(_reference->getGlobalBounds()))
		_active->collision[DOWN] = true;
	act.height -= _active->getMovementSpeed() + _range;
	act.left -= _active->getMovementSpeed() + _range;
	if (act.intersects(_reference->getGlobalBounds()))
		_active->collision[LEFT] = true;
	act.left += _active->getMovementSpeed() + _range;
	act.width += _active->getMovementSpeed() + _range;
	if (act.intersects(_reference->getGlobalBounds()))
		_active->collision[RIGHT] = true;
}


void Engine::createEnemies(int number)
{	
	for (int i = 0; i < number; i++) //przeciwnicy
	{
		float x, y;
		bool ok = false;
		while (!ok)
		{
			x = (float)(rand() % window_size_x);
			y = (float)(rand() % window_size_y) +20;
			if (y > 660)
				continue;
			ok = true;
		}

		int type = rand() % 2;
		switch (type)
		{
		case 0:
			enemies.push_back(new Enemy("opponent", 100, 2, x, y));
			break;
		case 1:
			enemies.push_back(new Enemy("opponent2", 100, 2, x, y));
			break;
		}		
	}
}

void Engine::createTower(sf::Vector2i pos)
{
	delete tiles[pos.x][pos.y];
	tiles[pos.x][pos.y] = new Tower(tileset, sf::Vector2i(7, 15), (float)pos.x, (float)pos.y, 10, 30, 20, 100);
}

void Engine::deleteTower(sf::Vector2i pos)
{
	delete tiles[pos.x][pos.y];
	tiles[pos.x][pos.y] = new Tile(tileset, sf::Vector2i(0, 0), (float)pos.x, (float)pos.y, GRASS);
}

void Engine::refresh()
{
	window.clear();
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 20; j++)
			window.draw(*tiles[i][j]);
	for (vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		window.draw(**it);
	window.draw(*player);
	for (list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
		window.draw(**it);
	window.draw(stat);
	window.draw(info);
	window.display();

	for (list<Bullet*>::iterator act = bullets.begin(); act != bullets.end(); ++act)
		if ((*act)->destroy)
		{
			delete (*act);
			bullets.erase(act);
			act--;
		}
	for (vector<Enemy*>::iterator act = enemies.begin(); act != enemies.end(); ++act)
		if ((*act)->dead)
		{
			delete (*act);
			enemies.erase(act);
			act--;
		}
	for(int i=0; i<40; i++)
		for (int j = 0; j < 20; j++)
			if (Tower* tmp = dynamic_cast<Tower*>(tiles[i][j]))
				if (tmp->hp <= 0)
					deleteTower(sf::Vector2i(i, j));
}


string Engine::status()
{
	string tmp;
	sf::Time time = clock.getElapsedTime();
	if (pause)
		tmp += "~~PAUSED~~\t";
	tmp += "SEC: ";
	tmp += to_string(frame_counter / 60);
	tmp += '\t';
	tmp += to_string(time.asSeconds());
	tmp += "\tFRAME: ";
	tmp += to_string(frame_counter);
	tmp += "\tPLAYER: (";
	tmp += to_string((int)player->getPosition().x);
	tmp += 'x';
	tmp += to_string((int)player->getPosition().y);
	tmp += ")\t";
	tmp += to_string(player->getPositionTile().x);
	tmp += 'x';
	tmp += to_string(player->getPositionTile().y);
	tmp += "\tMOUSE: ";
	tmp += to_string(mouse_tile.x);
	tmp += 'x';
	tmp += to_string(mouse_tile.y);
	tmp += "\tHP: ";
	tmp += to_string(player->getHP());
	tmp += "\tBULLETS: ";
	tmp += to_string(bullets.size());
	return tmp;
}
