#include "Excavation.h"
#include <iostream>


int random_a_to_b(int const a, int const b)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(a, b);
	return distribution(engine);
}

Excavation::Excavation(sf::RenderWindow* window, GameAssets* ga, 
	std::unique_ptr<Inventory>& inventory ) : inventory(inventory) {
	ga = ga;

	canDig = true; 
	//Construction de la grille de base avec un vecteur de cases
	for (int i = 0; i < nb_case * nb_case; i++) {
		Case thisCase(i / nb_case, i % nb_case, hightExc, widthExc, nb_case,
			ga,(float)offsetWindowX, (float)offsetWindowY);
		cases.push_back(thisCase);
	}

	//Tracé du cadre
	textCadre = ga->cadre;
	spriteCadre.setScale(1.5f,1.5f);
	spriteCadre.setPosition(sf::Vector2f(offsetWindowX-100, offsetWindowY-100));
	//Appelle de la fonction init
	init();

}

int Excavation::posMouse(sf::RenderWindow* window) //Retourne la position i de la case sur laquelle la souris est
{
	sf::Vector2i position = sf::Mouse::getPosition(*window);
	int x = (position.x - offsetWindowX) / (hightExc / nb_case) ;
	int y = (position.y - offsetWindowY) / (widthExc / nb_case) ;
	int value = x * nb_case + y;
	return value;
}

void Excavation::digIn(int val) //Creuse une case et vérifie si on a trouvé le trésor
{
	if (val >= 0 && val < nb_case * nb_case) {
		if (!(cases[val].getDig())) {
			tryDig++;
			cases[val].setDig(true);
			if (cases[val].getTresure()) {
				found++;
				if (found == toFound) {
					std::cout << "FOUND";
					inventory->display_all();
					inventory->add_material(materialToFound,1);
					inventory->display_all();
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
	maxX = 0;
	maxY = 0;


	//Recherche d'un objet aléatoire	
	auto& materials = inventory->get_materials();
	std::vector<string> keys;
	for (auto const& material : materials)
		keys.push_back(material.first);
	int rand = random_a_to_b(0, materials.size()-1);
	materialToFound = keys[rand];

	//Placement de l'objet
	auto shape = materials[materialToFound]->get_shape();

	for (auto& coor : shape) {
		objCoor.push_back(coor);
		maxX = maxX < get<0>(coor) ? get<0>(coor) : maxX;
		maxY = maxY < get<1>(coor) ? get<1>(coor) : maxY;
	}
	maxX++;
	maxY++;

	offsetX = random_a_to_b(0, nb_case-maxX);
	offsetY = random_a_to_b(0, nb_case - maxY);
	toFound = objCoor.size();
	found = 0;

	string stringSprite = materials[materialToFound]->get_sprite_path();
	for (auto& coor : objCoor) {
		int val = (get<0>(coor) + offsetX) * nb_case + get<1>(coor) + offsetY;
		cases[val].setTresure(stringSprite,maxX,maxY, get<0>(coor), get<1>(coor));
	}

	//Nombre de possibilité de creuser
	int pos = random_a_to_b(toFound, toFound+2*nb_case);
	nbDig = pos;
	tryDig = 0;

}

void Excavation::reset()
{
	canDig = false;
	//reset des cases
	for (int i = 0; i < nb_case * nb_case; i++) {
		cases[i].setDig(false);
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
	spriteCadre.setTexture(textCadre);
	//window->draw(spriteCadre);

	

}