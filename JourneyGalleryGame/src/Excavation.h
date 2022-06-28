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
#include <chrono>
#include <thread>

using namespace std;

//Taille de la fenetre
#define hightExc 800 
#define widthExc 800

//Deplacement de la fenetre
#define offsetWindowX 560
#define offsetWindowY 140

//Nombre de case
#define nb_case 4

class Excavation
{
public:
	explicit Excavation(sf::RenderWindow* window, GameAssets* ga, std::unique_ptr<Inventory>& inventory);
	void draw(sf::RenderWindow* window);
	int posMouse(sf::RenderWindow* window);
	void digIn(int val);
	void updateInput(sf::RenderWindow* window);
	void init();
	void reset();
	bool getCanDig();
	void foundTreasure();
	void setCanDig(bool state);
	void setDrawing(bool state);
	void dig(int val);

private:
	GameAssets* ga;

	std::vector<Case> cases;

	std::unique_ptr<Inventory>& inventory;
	string materialToFound;
	vector<std::tuple<int, int> > objCoor; //objet a trouver

	int maxX; //largeur max
	int maxY; //longeur max
	int offsetX; //offset de x sur la grille
	int offsetY; //offset de y sur la grille

	int tryDig; //nombre de tentative
	int nbDig; //nombre de tentative possible
	int found; //nombre de morceau de trésor trouvé
	int toFound; //nombre de morceau a trouvé

	bool canDig; //Si on peut creuser -> lui qui fait passer au state inendexcavation

	bool isDrawing; //Pour savoir si il faut draw la grille ou non



	sf::Texture textCadre;
	sf::Sprite spriteCadre;

	sf::Texture textPelle1;
	sf::Sprite spritePelle1;
	sf::Texture textPelle2;
	sf::Sprite spritePelle2;
	sf::Texture textPelle3;
	sf::Sprite spritePelle3;

};