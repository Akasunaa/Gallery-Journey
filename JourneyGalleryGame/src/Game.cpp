#include "Game.h"
#include <MyContactListener.h>




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
	this->player = new Player(world, { 100.0f, 0.0f });

	//init wall
	this->wall = new WallPiece(world, { 0.0f, 0.0f });

	//Init ground
	/*b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f,-200.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(10000.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);*/

}

Game::Game() {
	this->initVariable();
	this->initWindow();
	//system("dir");


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

	this->wall->draw((this->window));
	this->player->playerDraw((this->window));

	this->window->display();
}
