#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>
#include <string.h>
#include <GameAssets.h>

//Cette classe g�re les cases affich�s lorsqu'on creuse, c'est � dire leur contenu et leur �tat 
class Case
{
public:
	explicit Case(int x,int y, float height, float width, float nb_case, 
		GameAssets* ga, float offsetWindowX,float offsetWindowY);
	void draw(sf::RenderWindow* window);
	void setDig(bool state); //Permet de dire que la case est creus�e
	bool getDig();


	void setTresure(std::string stringTreasure, int maxX, int maxY, int coorX, int coorY);
	void setUntresure();
	bool getTresure();

private:
	int x;
	int y;
	bool asTresure;
	bool isDig;

	float height;
	float width; 
	float nb_case;


	float offsetWindowX;
	float offsetWindowY;

	sf::Texture textureUndig;
	sf::Sprite spriteUndig;

	sf::Texture textureDig;
	sf::Sprite spriteDig;

	sf::Texture textTreasure;
	sf::Sprite spriteTreasure;

	GameAssets* ga;

};