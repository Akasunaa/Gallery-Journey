#include "WallPiece.h"
#include <iostream>

WallPiece::WallPiece(b2World* world, float x, float y, GameAssets* ga) : 
	InterractableObject{world, x,y, widthWall,heightWall, ga}
{
	canBeDug = true;
	texture = ga->wallpiece;
	sprite.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
	sprite.setScale((float)widthWall /texture.getSize().x, (float)heightWall / texture.getSize().y);
}

void WallPiece::setCanBeDug(bool state)
{
	canBeDug = state;
}

bool WallPiece::getCanBeDug()
{
	return canBeDug;
}

void WallPiece::draw(sf::RenderWindow* window)
{	
	if (canBeDug) {
		sprite.setTexture(texture);
		window->draw(sprite);
	}
	if (canInteract) {

		window->draw(textInteract);
	}
	
}




