#include "WallPiece.h"
#include <iostream>

WallPiece::WallPiece(b2World* world, float x, float y) : InterractableObject{world, x,y,heightWall, widthWall}
{

}

void WallPiece::interact()
{
	canInteract = true;
}

void WallPiece::dontInteract()
{
	canInteract = false;
}

void WallPiece::checkInteract()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && canInteract) {
		std::cout << "graou";

	}
}





