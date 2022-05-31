#include "Excavation.h"
#include <iostream>

Excavation::Excavation(sf::RenderWindow* window) {
	//Construction de la grille de base avec un vecteur de cases
	this->rect.setSize(sf::Vector2f(widthExc, hightExc));
	this->rect.setFillColor(sf::Color::White);
	for (int i = 0; i < nb_case*nb_case; i++) {
		Case thisCase(i / nb_case,i%nb_case,hightExc,widthExc,nb_case,i);
		cases.push_back(thisCase);
	}
	//Recherche d'un objet aléatoire
	object.push_back(make_tuple(0, 1));
	object.push_back(make_tuple(1, 1));
	object.push_back(make_tuple(1, 2));
	offsetX = 1;
	offsetY = 0;
	toFound = 3;
	found = 0;

	//Mise en place de l'objet 
	for (auto& coor : object) {
		int val = (get<0>(coor) + offsetX) * nb_case + get<1>(coor) + offsetY;
		std::cout << val << '\n';
		cases[val].setTresure();
	}

}
 
int Excavation::posMouse(sf::RenderWindow* window) //Retourne la position i de la case sur laquelle la souris est
{
	sf::Vector2i position = sf::Mouse::getPosition(*window);
	int x = position.x / (hightExc/nb_case);
	int y = position.y / (widthExc / nb_case);
	int value = x * nb_case + y;
	return value;
}

void Excavation::updateInput(sf::RenderWindow* window)
{
	//Creuse la case sur laquelle on est et verifie si on le débloque
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		int val = posMouse(window);
		if (val >= 0 && val < nb_case * nb_case) {
			cases[val].dig();
			std::cout << found << ' ' << toFound << '\n';

			if (cases[val].getTresure()) {
				found++;
				if (found == toFound) {
					std::cout << "FOUND";
				}
			}
		}


	}
}


void Excavation::draw(sf::RenderWindow* window)
{
	updateInput(window);
	for (int i = 0; i < nb_case*nb_case;i++) {
		cases[i].draw(window);	
	}

}

