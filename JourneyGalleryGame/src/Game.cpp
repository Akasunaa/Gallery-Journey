#include "Game.h"


void Game::loadLevel(b2World* world, Player* player, 
	sf::RenderWindow* window, int levelNumber,GameAssets* ga)
{
	std::string stringName = "resources/xml_files/level" + std::to_string(levelNumber) + ".xml";
	const char* charName = stringName.c_str();
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(charName);
	if (!result)
	{
		std::cerr << "Could not open file " << stringName << " because " << result.description() << std::endl;
		return;
	}
	pugi::xml_node levelData = doc.child("LevelData");
	for (auto child : levelData.children()) {
		if(child.name()=="Wall"sv){
			std::unique_ptr<Wall> wall = std::make_unique<Wall>(world,child, window, ga, player->get_inventory());
			walls.push_back(std::move(wall));
		}
		if (child.name() == "Door"sv) {
			std::unique_ptr<Door> door = std::make_unique<Door>(world, child, ga, player->get_inventory());
			doors.push_back(std::move(door));
		}
		if (child.name() == "Table") {
			std::unique_ptr<Table> table = std::make_unique<Table>(world, child,ga);
			tables.push_back(std::move(table));
		}
		
	}

}

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

	//init level
	indiceLevel=1;
	loadLevel(world, player, window, indiceLevel, ga);

	indispo = 0;

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
					for (auto& table : tables) {
						if (table->checkInteract()) {
							std::cout << "bro wat";
						}
					}

				}
			}
			else if (this->ev.key.code == sf::Keyboard::Q) {
				if (states == States::inExcavation) {
					digIndex = -1;
					states = States::inGame;
				}
			}
		}
	}

}

void Game::update()
{
	//Interaction input
	this->pollEvents();

	//InGame
	if (states == States::inGame) {
		player->updateInput();
	}
	//InExcavation -> code � d�placer?
	if (states == States::inExcavation) {
		//Verifie qu'on peut toujours creuser, sinon on se fait virer du mur
		if (!(walls[digIndex]->getExcavation()->getCanDig())) {
			walls[digIndex]->getWallPiece()->setCanBeDug(false);
			indispo++;
			states = States::inFinishExcavation;
			time(&start);
			//#sprint d'os #j'ai la flemme #ca prend trop de place dans le game
			if (indispo > 2) {
				//Initialisation
				int maxPrio = walls[digIndex]->getPrio();
				int toReactive = digIndex;
				//Boucle pour trouver celui a reactiver
				for(int i = 0; i < walls.size();i++) {
					if (!(walls[i]->getExcavation()->getCanDig())) {
						walls[i]->setPrio(walls[i]->getPrio() + 1);
						if (walls[i]->getPrio() > maxPrio) {
							toReactive = i;
							maxPrio = walls[i]->getPrio();
						}
					}
				}
				walls[toReactive]->reactiv();
				indispo--;
			}
		}
		if (states == States::inFinishExcavation) {
			//TODO :popup 
			time_t end;
			do time(&end); while (difftime(end, start) <= 2.5);
			states = States::inGame;

			}

		}

	if (player->getPosition().x < 50) {
		player->setPosition(b2Vec2(1700, player->getPosition().y));
		walls.clear();
		doors.clear();
		tables.clear();
		loadLevel(world, player, window, indiceLevel+1, ga);
		indiceLevel++;
	}
	if (player->getPosition().x > 1750) {
		player->setPosition(b2Vec2(100, player->getPosition().y));
		walls.clear();
		doors.clear();
		tables.clear();
		loadLevel(world, player, window, indiceLevel-1, ga);
		indiceLevel--;
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
		for (auto& door :doors) {
			door->draw((this->window));
		}
		for (auto& wall : walls) {
			wall->getWallPiece()->draw((this->window));
		}
		for (auto& door : doors) {
			door->draw((this->window));
		}
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


