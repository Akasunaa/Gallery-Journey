#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Player.h>
#include <WallPiece.h>
#include "box2d/box2d.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <MyContactListener.h>
#include <memory>
#include <vector>
#include "Excavation.h"
#include <Table.h>

class Game;

enum class States { inGame = 1, inExcavation = 2};

struct Wall {
	WallPiece wallPiece;
	Excavation excavation;
	Wall(b2World* world, float x, float y, sf::RenderWindow* window) :
		wallPiece(world, x, y),excavation(window){}
};

class Game {
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	float timeStep;
	int32 velocityIterations;
	int32 positionIterations;

	b2World* world;
	Player* player;

	unique_ptr<Table> table;
	std::vector<std::unique_ptr<Wall>> walls;
	Excavation* toDraw;


	void initWindow();
	void initWorld();

	States states;

public :
	Game();
	virtual ~Game();

	const bool running() const;


	void pollEvents();
	void update();
	void render();

};