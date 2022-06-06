#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Player.h>
#include "box2d/box2d.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <MyContactListener.h>
#include <memory>
#include <vector>
#include <Wall.h>
#include <Table.h>
#include <GameAssets.h>
#include <../imgui_lib/imgui.h>
#include <../imgui_lib/imgui-SFML.h>
#include <Door.h>

class Game;

enum class States { inGame = 1, inExcavation = 2, inMuseum=3};



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

	sf::Texture textBackground;
	sf::Sprite spriteBackground;


	GameAssets* ga;

	unique_ptr<Table> table;
	unique_ptr<Door> door;
	std::vector<std::unique_ptr<Wall>> walls;
	int digIndex; //mur en cours de creusage
	int indispo;


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

    sf::RenderWindow* & get_window();

};