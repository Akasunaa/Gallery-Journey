#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Player.h>
#include "box2d/box2d.h"
#include <stdio.h>
#include <assert.h>
#include <tmxlite/Map.hpp>
#include <iostream>

class Game {
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	Player* player;
	b2World* world;

	float timeStep;
	int32 velocityIterations;
	int32 positionIterations;

	void initVariable();
	void initWindow();

public :
	Game();
	virtual ~Game();

	const bool running() const;


	void pollEvents();
	void update();
	void render();

};