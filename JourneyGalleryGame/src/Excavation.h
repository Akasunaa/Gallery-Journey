#pragma once
#include "Case.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>
#include <random>
#include <Inventory.h>
#include <Material.h>
#include <memory>
using namespace std;


#define hightExc 400
#define widthExc 400

#define nb_case 4

class Excavation
{
public:
	explicit Excavation(sf::RenderWindow* window,GameAssets* ga, Inventory* inventory);
	void draw(sf::RenderWindow* window);
	int posMouse(sf::RenderWindow* window);
	void digIn(int val);
	void updateInput(sf::RenderWindow* window);
	void init();
	void reset();
	bool getCanDig();

private:
	GameAssets* ga;

	sf::RectangleShape rect;
	std::vector<Case> cases;

	Inventory* inventory; 
	vector<std::tuple<int, int> > objCoor; //objet a trouver


	int offsetX; //offset de x sur la grille
	int offsetY; //offset de y sur la grille

	int tryDig; //nombre de tentative
	int nbDig; //nombre de tentative possible
	int found; //nombre de morceau de trésor trouvé
	int toFound; //nombre de morceau a trouvé

	bool canDig; //Si on peut creuser
};