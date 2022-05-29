#include "WallPiece.h"
#include <iostream>

WallPiece::WallPiece(b2World* world, b2Vec2 pos) : InterractableObject{world, pos,heightWall, widthWall}
{
	
}

void WallPiece::interact()
{
	std::cout << "ouaf";
}



