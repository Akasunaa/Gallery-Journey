#include "Game.h"




void Game::initVariable()
{
	this->window = nullptr;
	this->player = nullptr;
	this->world = nullptr;
}

void Game::initWindow()
{
	//init fenetre
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window= new sf::RenderWindow(this->videoMode, "SFML window", sf::Style::Titlebar | sf::Style::Close);

	//init world
	b2Vec2 gravity(0.0f, 0.0f);
	this->world = new b2World(gravity);
	timeStep = 1.0f / 60.0f;
	velocityIterations = 6;
	positionIterations = 2;


	//Init player
	this->player = new Player(world, { 0.0f, 0.0f });

	//test mur


}

Game::Game() {
	this->initVariable();
	this->initWindow();

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
	this->world->Step(timeStep, velocityIterations, positionIterations);
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
			break;
		}
	}

	player->updateInput();

}

void Game::update() 
{
	this->pollEvents();
}



void Game::render()
{

	this->window->clear();
	this->player->playerDraw((this->window), { -400.0f, -400.0f });


	//Afficher la tilemap


	this->window->display();
}
