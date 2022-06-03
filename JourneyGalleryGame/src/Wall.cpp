#include "Wall.h"

Wall::Wall(b2World* world, float x, float y, sf::RenderWindow* window, 
	GameAssets* ga, std::unique_ptr<Inventory>& inventory)
{
	wallPiece = new WallPiece(world, x, y);
	excavation = new Excavation(window,ga,inventory);
	prio = 0;
}

int Wall::getPrio()
{
	return prio;
}

WallPiece* Wall::getWallPiece()
{
	return wallPiece;
}

Excavation* Wall::getExcavation()
{
	return excavation;
}

void Wall::update()
{
	//nothing to do here
}
