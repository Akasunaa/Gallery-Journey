#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <random>
#include <WallPiece.h>
#include <Excavation.h>


class Wall
{
public:
	Wall(b2World* world, float x, float y, sf::RenderWindow* window);
	int getPrio();
	WallPiece* getWallPiece();
	Excavation* getExcavation();
	void update();

private:
	WallPiece* wallPiece;
	Excavation* excavation;
	int prio;

};