#include "Game.h"




void Game::initWindow()
{
	//init fenetre
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window= new sf::RenderWindow(this->videoMode, "SFML window", sf::Style::Titlebar | sf::Style::Close);
}

void Game::initWorld()
{
	//init world
	b2Vec2 gravity(0.0f, 0.0f);
	this->world = new b2World(gravity);

	//init time
	timeStep = 1.0f / 60.0f;
	velocityIterations = 6;
	positionIterations = 2;

	//init state
	states = States::inGame;

	//init level
	this->player = new Player(world, { 200.0f, 0.0f });

	//init walls

	std::unique_ptr<Wall> wall = std::make_unique<Wall>(world, 0.0f, 0.0f,this->window);
	std::unique_ptr<Wall> walltwo = std::make_unique<Wall>(world, 300.0f, 0.0f, this->window);
	walls.push_back(std::move(wall));
	walls.push_back(std::move(walltwo));

	table = std::make_unique<Table>(world, 400.0f, 0.0f);
	//Init ground
	/*b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f,-200.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(10000.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);*/
}




Game::Game() {
	this->initWindow();
	this->initWorld();
}

Game::~Game() {
	delete this->window;
	delete this->player;
	delete this->world;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	MyContactListener myContactListenerInstance;

	this->world->Step(timeStep, velocityIterations, positionIterations);
	world->SetContactListener(&myContactListenerInstance);

	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			else if (this->ev.key.code == sf::Keyboard::E) { //Boucle d'interaction avec les objets 
				if (states == States::inGame) {
					//Interraction avec les murs

					for (int i = 0; i < walls.size(); i++)
					{
						if (walls[i]->wallPiece.checkInteract()) {
							if (walls[i]->excavation.getIsActiv()) {
								states = States::inExcavation;
								digIndex = i;
							}
						}
					}
					//Interraction avec la table
					if (table->checkInteract()) { 
						std::cout << "bro wat";
					}
				}
			}
			else if (this->ev.key.code == sf::Keyboard::Q) {
				if (states == States::inExcavation) {
					digIndex = -1;
					states = States::inGame;
				}
				break;
			}
		}
	}

}

void Game::update() 
{
	this->pollEvents();
	if(states==States::inGame)
		player->updateInput();
	if (states == States::inExcavation) {
		if (!(walls[digIndex]->excavation.getIsActiv())) {
			walls[digIndex]->wallPiece.setCanBeDug(false);
			states = States::inGame;
		}
	}
}



void Game::render()
{
	this->window->clear();
	for (auto& wall : walls) {
		wall->wallPiece.draw((this->window));
	}
	this->player->playerDraw((this->window));
	if (states == States::inExcavation) {
		walls[digIndex]->excavation.draw(this->window);
	}
	this->table->draw(this->window);
	
	this->window->display();
}


