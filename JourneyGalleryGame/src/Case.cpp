#include "Case.h"
#include <iostream>


Case::Case(int x, int y,float height, float width, float nb_case,int value,
	GameAssets* ga, float offsetWindowX, float offsetWindowY)
{
	ga=ga;
	this->x = x;
	this->y = y;
	this->value = value;
	this->rect.setSize(sf::Vector2f(height/nb_case,width/nb_case));
	this->rect.setFillColor(sf::Color::Red);
	this->rect.setPosition(sf::Vector2f((x * height /nb_case) +offsetWindowX, (y * width/nb_case)+offsetWindowY));
	this->rect.setOutlineColor(sf::Color::Black);
	this->rect.setOutlineThickness(-3);
	this->isDig = false;
	this->asTresure = false;

	offsetWindowX = offsetWindowX;
	offsetWindowY = offsetWindowY;

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
			this->rect.setFillColor(sf::Color::Yellow);
			window->draw(rect);
		}
	}
	else {
		window->draw(spriteUndig);

	}

	
	
}

void Case::setDig()
{
	isDig = true;
	if(asTresure){
		this->rect.setFillColor(sf::Color::Yellow);
	}
	else {
		this->rect.setFillColor(sf::Color::Blue);
	}

}

bool Case::getTresure()
{
	return asTresure;
}

bool Case::getDig()
{
	return isDig;
}

void Case::setUndig()
{
	isDig = false;
	this->rect.setFillColor(sf::Color::Red);
}

void Case::setTresure()
{
	asTresure = true;
}

void Case::setUntresure()
{
	asTresure = false;
}



