#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <random>
#include <WallPiece.h>
#include <Excavation.h>
#include <Player.h>


class Wall
{
public:
	Wall(b2World* world, float x, float y, sf::RenderWindow* window, GameAssets* ga,std::unique_ptr<Inventory>& inventory);
	Wall(b2World* world, pugi::xml_node node, sf::RenderWindow* window, GameAssets* ga, std::unique_ptr<Inventory>& inventory);
	int getPrio();
	void setPrio(int val);
	WallPiece* getWallPiece();
	Excavation* getExcavation();
	void reactiv();
	void reset();

	void update();

private:
	WallPiece* wallPiece;
	Excavation* excavation;
	int prio;

};