#include "Game.h"
#include "pugixml.hpp"
#include <cstdlib>
#define INVENTORY_XML_PATH "resources/xml_files/inventory.xml"


void Game::initWindow()
{
	//init fenetre
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window= new sf::RenderWindow(this->videoMode, "SFML window", sf::Style::Titlebar | sf::Style::Close);
}

void Game::initWorld()
{
	//init asset
	
	ga = new GameAssets();

	//init world
	b2Vec2 gravity(0.0f, 0.0f);
	this->world = new b2World(gravity);

	//init time
	timeStep = 1.0f / 60.0f;
	velocityIterations = 6;
	positionIterations = 2;

	//init state
	states = States::inGame;

	//init player & its inventory
    pugi::xml_document inventory_doc;
    pugi::xml_parse_result result = inventory_doc.load_file(INVENTORY_XML_PATH);
    if (!result)
    {
        std::cerr << "Could not open file inventory.xml because " << result.description() << std::endl;
        exit(1);
    }
	this->player = new Player(world, { 200.0f, 0.0f }, inventory_doc.child("Inventory"));

	//init walls
	std::unique_ptr<Wall> wall = std::make_unique<Wall>(world, 0.0f, 0.0f,this->window,ga,player->get_inventory());
	std::unique_ptr<Wall> walltwo = std::make_unique<Wall>(world, 200.0f, 0.0f, this->window,ga,player->get_inventory());
	std::unique_ptr<Wall> wallthree = std::make_unique<Wall>(world, 300.0f, 0.0f, this->window,ga,player->get_inventory());
	walls.push_back(std::move(wall));
	walls.push_back(std::move(walltwo));
	walls.push_back(std::move(wallthree));
	indispo = 0;
	//init table
	table = std::make_unique<Table>(world, 400.0f, 0.0f);

	//Init ground
	/*b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f,-200.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(10000.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);*/
}




Game::Game() {
	this->initWindow();
	this->initWorld();
}

Game::~Game() {
	delete this->window;
	delete this->player;
	delete this->world;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	MyContactListener myContactListenerInstance;
	this->world->Step(timeStep, velocityIterations, positionIterations);
	world->SetContactListener(&myContactListenerInstance);

	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			else if (this->ev.key.code == sf::Keyboard::E) { //Boucle d'interaction avec les objets 
				if (states == States::inGame) {
					//Interraction avec les murs
					for (int i = 0; i < walls.size(); i++)
					{
						if (walls[i]->getWallPiece()->checkInteract()) {
							if (walls[i]->getExcavation()->getCanDig()) {
								states = States::inExcavation;
								digIndex = i; //Mur que l'on est en train de creuser
							}
						}
					}
					//Interraction avec la table
					if (table->checkInteract()) { 
						std::cout << "bro wat";
					}
				}
			}
			else if (this->ev.key.code == sf::Keyboard::Q) {
				if (states == States::inExcavation) {
					digIndex = -1;
					states = States::inGame;
				}
				break;
			}
		}
	}

}

void Game::update()
{
	//Interaction input
	this->pollEvents();

	//InGame
	if (states == States::inGame)
		player->updateInput();

	//InExcavation -> code � d�placer?
	if (states == States::inExcavation) {
		//Verifie qu'on peut toujours creuser, sinon on se fait virer du mur
		if (!(walls[digIndex]->getExcavation()->getCanDig())) {
			walls[digIndex]->getWallPiece()->setCanBeDug(false);
			states = States::inGame;
			//Si on retourne en jeu, on cherche un autre mur � rendre actif
			//Boucle sur les non actifs pour trouver celui � reveiller #sprint 1 d'os moins bien cod�			
		}
	}
}




void Game::render()
{
	this->window->clear();

	//Dessin de la table
	this->table->draw(this->window);
	//Dessin des walls
	for (auto& wall : walls) {
		wall->getWallPiece()->draw((this->window));
	}
	//Dessin du player
	this->player->playerDraw((this->window));
	//Dessin de l'extraction
	if (states == States::inExcavation) {
		walls[digIndex]->getExcavation()->draw(this->window);
	}

	
	this->window->display();
}


