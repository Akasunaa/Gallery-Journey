#include "Game.h"


void Game::loadLevel(b2World* world,
	sf::RenderWindow* window, int levelNumber, GameAssets* ga)
{
	//Destruction des objets de l'ancien niveau
	for (auto& table : tables)
	{
		world->DestroyBody(table->getBodyPointer());
	}
	for (auto& door : doors) {

		world->DestroyBody(door->getBodyPointer());
	}
	for (auto& wall : walls) {

		world->DestroyBody(wall->getWallPiece()->getBodyPointer());
	}
	walls.clear();
	doors.clear();
	tables.clear();
	skeletons.clear();

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
		if (child.name() == "Wall"sv) {
			std::unique_ptr<Wall> wall = std::make_unique<Wall>(world, child, window, ga, player->get_inventory());
			walls.push_back(std::move(wall));
		}
		if (child.name() == "Door"sv) {
			std::unique_ptr<Door> door = std::make_unique<Door>(world, child, ga, player->get_inventory());
			doors.push_back(std::move(door));
		}
		if (child.name() == "Table"sv) {
			std::unique_ptr<Table> table = std::make_unique<Table>(world, child, ga);
			tables.push_back(std::move(table));
		}
		if (child.name() == "Skeleton"sv) {
			std::unique_ptr<Skeleton> skeleton = std::make_unique<Skeleton>(world, child, ga, player->get_inventory());
			skeletons.push_back(std::move(skeleton));
		}

	}

}

void Game::initWindow()
{
	//init fenetre
	this->videoMode.height = 1080;
	this->videoMode.width = 1920;
	this->window = new sf::RenderWindow(this->videoMode, "Gallery Journey", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(120);
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
	velocityIterations = 10;
	positionIterations = 10;

	//init state
	states = States::inGame;

	//init background
	textBackground = ga->background;
	spriteBackground.setPosition(sf::Vector2f(0, 0));
	spriteBackground.setScale(0.5, 0.5);


	//init player & its inventory
	pugi::xml_document inventory_doc;
	pugi::xml_parse_result result = inventory_doc.load_file(INVENTORY_XML_PATH);
	if (!result)
	{
		std::cerr << "Could not open file inventory.xml because " << result.description() << std::endl;
		exit(1);
	}
	this->player = new Player(world, { 1000.0f, 650.0f }, inventory_doc.child("Inventory"), ga);

	//init level
	indiceLevel = 1;
	loadLevel(world, window, indiceLevel, ga);


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

void Game::electWall()
{
	if (indispo > walls.size() / 2) {
		//Initialisation
		int maxPrio = walls[digIndex]->getPrio();
		int toReactive = digIndex;
		//Boucle pour trouver celui a reactiver
		for (int i = 0; i < walls.size(); i++) {
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



void Game::switchLevel()
{
	if (player->getPosition().x < 50) {
		indiceLevel++;
		loadLevel(world, window, indiceLevel, ga);
		player->setPosition(b2Vec2(1760, 650.0f));
	}
	if (player->getPosition().x > 1780) {
		indiceLevel--;
		loadLevel(world, window, indiceLevel, ga);
		player->setPosition(b2Vec2(100, 650.0f));
	}

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
			switch (this->ev.key.code) {
			case sf::Keyboard::Escape:
				this->window->close();
				break;
			case sf::Keyboard::E:
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
							player->stop();
							states = States::inCraft;
						}

					}
					for (auto& door : doors) {
						if (door->checkInteract()) {
							if (door->isUnlockable()) {
								door->unlock();
							}
						}

					}
				}
				break;
			case sf::Keyboard::Q:
				switch (states) {
				case States::inExcavation:
					digIndex = -1;
				case States::inInventory:
				case States::inCraft:
					states = States::inGame;
					break;
				}
				break;
			case sf::Keyboard::I:
				switch (states) {
				case States::inGame:
					player->stop();
					states = States::inInventory;
					break;
				case States::inInventory:
					states = States::inGame;
					break;

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

	switch (states)
	{
	case States::inExcavation:
		if (!(walls[digIndex]->getExcavation()->getCanDig())) {
			time(&start);
			states = States::inFinishExcavation;
		}
		break;
	case States::inFinishExcavation:
		time_t end;
		time(&end);

		if (difftime(end, start) > 2) {
			states = States::inGame;
			start = 0;
			indispo++;
			walls[digIndex]->reset();
            player->get_inventory()->clear_just_found();
			electWall();
		}
		break;
	case States::inInventory:
		break;
	case States::inCraft:
		break;
	case States::inGame:
		player->updateInput();
		for (auto& skeleton : skeletons) {
			if (skeleton->isUnlockable())
				skeleton->unlock();
		}
		break;
	}
	switchLevel();
}


void Game::render()
{
	this->window->clear();
	spriteBackground.setTexture(textBackground);
	this->window->draw(spriteBackground);

	switch (states)
	{
	case States::inFinishExcavation:
        this->player->get_inventory()->draw_pop_up_found();
    case States::inExcavation:
		walls[digIndex]->getExcavation()->draw(this->window);
		break;
	case States::inInventory:
		this->player->get_inventory()->draw_inventory_screen();
		break;
	case States::inCraft:
		this->player->get_inventory()->draw_craft_screen();
		break;
	case States::inGame:
		for (auto& wall : walls) {
			wall->getWallPiece()->draw((this->window));
		}

		for (auto& door : doors) {
			door->draw((this->window));
		}
		for (auto& table : tables) {
			table->draw((this->window));
		}
		for (auto& skeleton : skeletons) {
			skeleton->draw((this->window));
		}
		this->player->playerDraw((this->window));
		draw_commands_window();
		break;
	}
	ImGui::SFML::Render(*window);
	this->window->display();
}

sf::RenderWindow*& Game::get_window() {
	return window;
}

void Game::draw_commands_window() {
	ImGui::Begin("Aide", NULL, ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2(WINDOW_W * 4 / 5, 0));
	ImGui::SetWindowFontScale(2);
	ImGui::SetWindowSize(ImVec2(WINDOW_W / 5, WINDOW_H / 5.5));
	ImGui::Text("Interagir : E ");
	ImGui::Text("Inventaire : I ");
	ImGui::Text("Se déplacer : <- et -> ");
	ImGui::Text("Quitter un écran : Q ");
	ImGui::Text("Creuser : Clic Gauche");
	ImGui::End();
}

