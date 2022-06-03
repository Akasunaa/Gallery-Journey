#include "Case.h"
#include <iostream>


Case::Case(int x, int y,float height, float width, float nb_case,int value,GameAssets* ga)
{
	ga=ga;
	this->x = x;
	this->y = y;
	this->value = value;
	this->rect.setSize(sf::Vector2f(height/nb_case,width/nb_case));
	this->rect.setFillColor(sf::Color::Red);
	this->rect.setPosition(sf::Vector2f(x * height /nb_case, y * width/nb_case));
	this->rect.setOutlineColor(sf::Color::Black);
	this->rect.setOutlineThickness(-3);
	this->isDig = false;
	this->asTresure = false;
	textureUndig = ga->wallUndig;
	spriteUndig.setPosition(sf::Vector2f(x * height / nb_case, y * width / nb_case));
	spriteUndig.setScale((height / nb_case)/textureUndig.getSize().x, (width / nb_case) / textureUndig.getSize().y);
	
	textureDig = ga->wallDig;
	spriteDig.setPosition(sf::Vector2f(x * height / nb_case, y * width / nb_case));
	spriteDig.setScale((height / nb_case) / textureDig.getSize().x, (width / nb_case) / textureDig.getSize().y);
}

void Case::draw(sf::RenderWindow* window)
{
	spriteUndig.setTexture(textureUndig);
	spriteDig.setTexture(textureDig);
	if (isDig) {
		window->draw(spriteDig);
	}
	else {
		window->draw(spriteUndig);
	}
	if (asTresure) {
		this->rect.setFillColor(sf::Color::Yellow);
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



