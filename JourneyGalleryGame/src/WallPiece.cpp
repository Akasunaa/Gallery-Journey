#include "WallPiece.h"
#include <iostream>

WallPiece::WallPiece(b2World* world, b2Vec2 pos) : InterractableObject{world, pos,heightWall, widthWall}
{
	canInteract = false;
}

void WallPiece::interact()
{
	canInteract = true;
}

void WallPiece::dontinteract()
{
	canInteract = false;
}

void WallPiece::checkInteract()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && canInteract) {
		std::cout << "graou";
	}
}





