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
	this->player = new Player(world, { 100.0f, 0.0f });
	this->excavation = new Excavation(this->window);

	//init walls


	std::unique_ptr<WallPiece> wall = std::make_unique<WallPiece>(world, 0.0f, 0.0f);
	walls.push_back(std::move(wall));
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
			else if (this->ev.key.code == sf::Keyboard::E) {
				if (states == States::inGame) {
					for (auto& wall : walls) {
						if (wall->checkInteract()) {
							states = States::inExcavation;
						}
					}
				}
			}
			else if (this->ev.key.code == sf::Keyboard::Q) {
				if (states == States::inExcavation) {
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
	player->updateInput();
	for (auto& wall : walls) {
		wall->checkInteract();
	}
}



void Game::render()
{
	this->window->clear();
	for (auto& wall : walls) {
		wall->draw((this->window));
	}
	this->player->playerDraw((this->window));
	if (states == States::inExcavation) {
		excavation->draw(this->window);
	}
	
	this->window->display();
}

