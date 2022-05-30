#include "Excavation.h"
#include <iostream>

Excavation::Excavation(sf::RenderWindow* window) {
	this->rect.setSize(sf::Vector2f(widthExc, hightExc));
	this->rect.setFillColor(sf::Color::White);
	for (int i = 0; i < nb_case*nb_case; i++) {
		Case thisCase(i / nb_case,i%nb_case,hightExc,widthExc,nb_case,i);
		cases.push_back(thisCase);

	}

}

int Excavation::posMouse(sf::RenderWindow* window)
{
	sf::Vector2i position = sf::Mouse::getPosition(*window);
	int x = position.x / (hightExc/nb_case);
	int y = position.y / (widthExc / nb_case);
	int value = x * nb_case + y;
	return value;
}

void Excavation::updateInput(sf::RenderWindow* window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		int val = posMouse(window);
		if(val>= 0 && val < nb_case*nb_case)
			cases[val].dig();

	}
}


void Excavation::draw(sf::RenderWindow* window)
{
	updateInput(window);
	for (int i = 0; i < nb_case*nb_case;i++) {
		cases[i].draw(window);
		
	}

}

