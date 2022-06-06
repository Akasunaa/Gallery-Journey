#include "Game.h"
#include "pugixml.hpp"
#include <cstdlib>
#define INVENTORY_XML_PATH "resources/xml_files/inventory.xml"


void Game::initWindow()
{
	//init fenetre
	this->videoMode.height = 1080;
	this->videoMode.width = 1920;
	this->window= new sf::RenderWindow(this->videoMode, "SFML window", sf::Style::Titlebar | sf::Style::Close);
    ImGui::SFML::Init(*window);
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

	//init background
	textBackground = ga->background;
	spriteBackground.setPosition(sf::Vector2f(0, 0));
	spriteBackground.setScale(0.5,0.5);

	//init player & its inventory
    pugi::xml_document inventory_doc;
    pugi::xml_parse_result result = inventory_doc.load_file(INVENTORY_XML_PATH);
    if (!result)
    {
        std::cerr << "Could not open file inventory.xml because " << result.description() << std::endl;
        exit(1);
    }
	this->player = new Player(world, { 1000.0f, 650.0f }, inventory_doc.child("Inventory"),ga);

	//init element
	std::unique_ptr<Wall> wall = std::make_unique<Wall>(world, 500.0f, 400.0f,this->window,ga,player->get_inventory());
	std::unique_ptr<Wall> walltwo = std::make_unique<Wall>(world, 200.0f, 400.0f, this->window,ga,player->get_inventory());
	std::unique_ptr<Wall> wallthree = std::make_unique<Wall>(world, 1100.0f, 400.0f, this->window,ga,player->get_inventory());
	std::unique_ptr<Wall> wallfour = std::make_unique<Wall>(world, 800.0f, 400.0f, this->window, ga, player->get_inventory());
	walls.push_back(std::move(wall));
	walls.push_back(std::move(walltwo));
	walls.push_back(std::move(wallthree));
	walls.push_back(std::move(wallfour));
	indispo = 0;
	table = std::make_unique<Table>(world, 1600.0f, 650.0f,ga);

	door = std::make_unique<Door>(world, 0.0f, 450.0f, ga, player->get_inventory());





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
        ImGui::SFML::ProcessEvent(ev);
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
								player->stop();
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
				else {
					door->unlock();
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
	if (states == States::inGame || states==States::inMuseum) {
		player->updateInput();
		if (player->getPosition().x > 1800) {
			player->setPosition(b2Vec2(200.0f, player->getPosition().y));
			door->setEnable(false);
			states = States::inMuseum;

		}
	}

	//InMuseum
	if (states == States::inMuseum) {
		if (player->getPosition().x < 100) {
			player->setPosition(b2Vec2(1700.0f, player->getPosition().y));
			door->setEnable(true);
			states = States::inGame;
		}
	}



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
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();

	spriteBackground.setTexture(textBackground);
	this->window->draw(spriteBackground);

	if (states == States::inGame) {
		//Dessin de la table
		this->table->draw(this->window);
		//Dessin des walls
		for (auto& wall : walls) {
			wall->getWallPiece()->draw((this->window));
		}
		this->door->draw(this->window);
	}
	//Dessin du player
	this->player->playerDraw((this->window));
	//Dessin de l'extraction
	if (states == States::inExcavation) {
		walls[digIndex]->getExcavation()->draw(this->window);
	}


    ImGui::SFML::Render(*window);

	this->window->display();
}

sf::RenderWindow* &Game::get_window() {
    return window;
}


