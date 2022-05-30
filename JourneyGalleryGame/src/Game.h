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

enum class States { inGame = 1, inExcavation = 2};
 

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
	Excavation* excavation;
	std::vector<std::unique_ptr<WallPiece>> walls;


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