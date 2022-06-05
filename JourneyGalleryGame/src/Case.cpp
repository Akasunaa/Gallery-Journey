#include "Case.h"
#include <iostream>


Case::Case(int x, int y,float height, float width, float nb_case,
	GameAssets* ga, float offsetWindowX, float offsetWindowY) : 
	x(x),y(y),ga(ga),height(height),width(width),nb_case(nb_case),
	offsetWindowX(offsetWindowX),offsetWindowY(offsetWindowY)
{

	isDig = false;
	asTresure = false;

	textureUndig = ga->wallUndig;
	spriteUndig.setPosition(sf::Vector2f((x * height / nb_case) + offsetWindowX, (y * width / nb_case) + offsetWindowY));
	spriteUndig.setScale((height / nb_case)/textureUndig.getSize().x, (width / nb_case) / textureUndig.getSize().y);
	
	textureDig = ga->wallDig;
	spriteDig.setPosition(sf::Vector2f((x * height / nb_case) + offsetWindowX, (y * width / nb_case) + offsetWindowY));
	spriteDig.setScale((height / nb_case) / textureDig.getSize().x, (width / nb_case) / textureDig.getSize().y);
}

void Case::draw(sf::RenderWindow* window)
{
	spriteUndig.setTexture(textureUndig);
	spriteDig.setTexture(textureDig);
	if (isDig) {
		window->draw(spriteDig);
		if (asTresure) {
			spriteTreasure.setTexture(textTreasure);

			window->draw(spriteTreasure);
		}
	}
	else {
		window->draw(spriteUndig);

	}

	
	
}

void Case::setDig(bool state)
{
	isDig = state;

}

bool Case::getTresure()
{
	return asTresure;
}

bool Case::getDig()
{
	return isDig;
}


void Case::setTresure(std::string stringTreasure, int maxX, int maxY, int coorX, int coorY)
{
	asTresure = true;
	textTreasure.loadFromFile("resources/images/" + stringTreasure);

	spriteTreasure.setPosition(sf::Vector2f((x * height / nb_case) + offsetWindowX, (y * width / nb_case) + offsetWindowY));


	int originX = textTreasure.getSize().x * (float)coorX / (float)maxX;
	int originY = textTreasure.getSize().y * (float)coorY / (float)maxY;
	int lenghtX = textTreasure.getSize().x * 1  / maxX;
	int lenghtY = textTreasure.getSize().y * 1 /maxY;
	spriteTreasure.setTextureRect(sf::IntRect(
		originX,
		originY,
		lenghtX,
		lenghtY));

	spriteTreasure.setScale((width / nb_case) * maxX / textTreasure.getSize().x, (width / nb_case) * maxY / textTreasure.getSize().y);
}

void Case::setUntresure()
{
	asTresure = false;
}



