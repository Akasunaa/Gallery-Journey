#include "Excavation.h"
#include <iostream>


int random_a_to_b(int const a, int const b)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(a, b);
	return distribution(engine);
}

Excavation::Excavation(sf::RenderWindow* window, GameAssets* ga, Inventory* inventory) {
	ga = ga;
	inventory = inventory;

	canDig = true; 
	//Construction de la grille de base avec un vecteur de cases
	this->rect.setSize(sf::Vector2f(widthExc, hightExc));
	for (int i = 0; i < nb_case * nb_case; i++) {
		Case thisCase(i / nb_case, i % nb_case, hightExc, widthExc, nb_case, i,ga);
		cases.push_back(thisCase);
	}
	init();

}

int Excavation::posMouse(sf::RenderWindow* window) //Retourne la position i de la case sur laquelle la souris est
{
	sf::Vector2i position = sf::Mouse::getPosition(*window);
	int x = position.x / (hightExc / nb_case);
	int y = position.y / (widthExc / nb_case);
	int value = x * nb_case + y;
	return value;
}

void Excavation::digIn(int val) //Creuse une case et vérifie si on a trouvé le trésor
{
	if (val >= 0 && val < nb_case * nb_case) {
		if (!(cases[val].getDig())) {
			tryDig++;
			cases[val].setDig();
			if (cases[val].getTresure()) {
				found++;
				if (found == toFound) {
					std::cout << "FOUND";
					canDig = false;
				}
			}
		}

	}
}

void Excavation::updateInput(sf::RenderWindow* window)
{
	//Creuse la case sur laquelle on est et verifie si on le débloque
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		int caseIndex = posMouse(window);
		digIn(caseIndex);
	}
}

void Excavation::init()
{
	nbDig = true;
	//Nombre de possibilité de creuser
	int pos = random_a_to_b(5, 10);
	nbDig = pos;
	tryDig = 0;

	//Recherche d'un objet aléatoire
	
	auto & materials = inventory->get_materials();
	int obj = random_a_to_b(0, materials.size());
	//int test = materials[obj]->get_nb_copies();

	


	objCoor.push_back(make_tuple(0, 1));
	objCoor.push_back(make_tuple(1, 1));
	objCoor.push_back(make_tuple(1, 2));
	offsetX = 1;
	offsetY = 0;
	toFound = 3;
	found = 0;

	//Mise en place de l'objet 
	for (auto& coor : objCoor) {
		int val = (get<0>(coor) + offsetX) * nb_case + get<1>(coor) + offsetY;
		cases[val].setTresure();
	}

}

void Excavation::reset()
{
	canDig = false;
	//reset des cases
	for (int i = 0; i < nb_case * nb_case; i++) {
		cases[i].setUndig();
		cases[i].setUntresure();
	}

}

bool Excavation::getCanDig()
{
	return canDig;
}


void Excavation::draw(sf::RenderWindow* window)
{
	updateInput(window);
	for (int i = 0; i < nb_case * nb_case; i++) {
		cases[i].draw(window);
	}
	if (tryDig > nbDig) {
		reset();
		tryDig = 0;	
	}

}