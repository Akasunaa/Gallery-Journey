#pragma once
#include "Case.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>
#include <random>
using namespace std;


#define hightExc 400
#define widthExc 400

#define nb_case 4

class Excavation
{
public:
	explicit Excavation(sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	int posMouse(sf::RenderWindow* window);
	void digIn(int val);
	void updateInput(sf::RenderWindow* window);
	int init();
	void reset();

private:
	sf::RectangleShape rect;
	std::vector<Case> cases;

	//Si j'ai le temps : faire de ceci une structure
	vector<std::tuple<int, int> > object; //objet a trouver
	int offsetX; //offset de x sur la grille
	int offsetY; //offset de y sur la grille

	int tryDig; //nombre de tentative
	int canDig; //nombre de tentative possible
	int found; //nombre de morceau de trésor trouvé
	int toFound; //nombre de morceau a trouvé
};