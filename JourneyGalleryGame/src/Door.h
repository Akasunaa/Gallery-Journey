#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdio.h>
#include <InteractableObject.h>
#include <Player.h>
#include <UnlockableElement.h>
#include <InteractableObject.h>

#define heightDoor 360
#define widthDoor 240
/*
Cette classe g�re les portes, qui sont des �l�ments � la fois interactif et d�blocable si notre joueur poss�de tout 
les �l�ments n�cessaire
*/
class Door : public UnlockableElement, public InterractableObject
{
public:
	explicit Door(b2World* world, pugi::xml_node node, GameAssets* ga, 
		std::unique_ptr<Inventory>& inventory);

	void draw(sf::RenderWindow* window);
    void draw_pop_up();
	void unlock() override;


private:
	sf::Sprite spriteOpenDoor;
	sf::Texture textureOpenDoor;

};