#include "GameAssets.h"

GameAssets::GameAssets()
{
    std::string resourceDirectory = "resources/images/";

    wallUndig.loadFromFile(resourceDirectory + "undig.png");
    wallDig.loadFromFile(resourceDirectory + "dig.png");

    background.loadFromFile(resourceDirectory + "backgroundfinalfinal.png");

    player.loadFromFile(resourceDirectory + "player.png");

    cadre.loadFromFile(resourceDirectory + "cadre.png");
}
