#include "Game.h"
#include <tmxlite/Map.hpp>
#include <iostream>



void Game::initVariable()
{
	this->window = nullptr;

	this->player = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	//this->videoMode.getDesktopMode;
	this->window= new sf::RenderWindow(this->videoMode, "SFML window", sf::Style::Titlebar | sf::Style::Close);

	//init Tiled

	this->player = new Player();


}

Game::Game() {
	this->initVariable();
	this->initWindow();

}

Game::~Game() {
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
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
	this->player->playerDraw((this->window));
	//this->window->draw(this->rect);

	//Afficher la tilemap


	this->window->display();
}
