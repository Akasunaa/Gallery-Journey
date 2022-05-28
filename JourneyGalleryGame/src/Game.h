#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Player.h>
#include <WallPiece.h>
#include "box2d/box2d.h"
#include <stdio.h>
#include <assert.h>
#include <tmxlite/Map.hpp>
#include <iostream>
#include <MyContactListener.h>

class Game {
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	Player* player;
	Player* player2;
	b2World* world;

	float timeStep;
	int32 velocityIterations;
	int32 positionIterations;

	WallPiece* wall;


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