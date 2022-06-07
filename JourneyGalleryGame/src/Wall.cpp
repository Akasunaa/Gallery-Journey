#include "Wall.h"

Wall::Wall(b2World* world, float x, float y, sf::RenderWindow* window, 
	GameAssets* ga, std::unique_ptr<Inventory>& inventory)
{
	wallPiece = new WallPiece(world, x, y,ga);
	excavation = new Excavation(window,ga,inventory);
	prio = 0;
}

Wall::Wall(b2World* world, pugi::xml_node node, sf::RenderWindow* window,
	GameAssets* ga, std::unique_ptr<Inventory>& inventory)
{
	float x = node.attribute("posX").as_float();
	float y = node.attribute("posY").as_float();
	wallPiece = new WallPiece(world, x, y, ga);
	excavation = new Excavation(window, ga, inventory);
	prio = 0;
}

int Wall::getPrio()
{
	return prio;
}

void Wall::setPrio(int val)
{
	prio = val;
}

WallPiece* Wall::getWallPiece()
{
	return wallPiece;
}

Excavation* Wall::getExcavation()
{
	return excavation;
}

void Wall::reactiv()
{
	excavation->init();
	wallPiece->setCanBeDug(true);
	excavation->setCanDig(true);
	prio = 0;
}

void Wall::update()
{
	//nothing to do here
}
