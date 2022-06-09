#include "GameAssets.h"

GameAssets::GameAssets()
{
    std::string resourceDirectory = "resources/images/";

    wallUndig.loadFromFile(resourceDirectory + "undig.png");
    wallDig.loadFromFile(resourceDirectory + "dig.png");

    background.loadFromFile(resourceDirectory + "backgroundfinalfinal.png");

    player.loadFromFile(resourceDirectory + "player.png");

    cadre.loadFromFile(resourceDirectory + "cadre.png");

    wallpiece.loadFromFile(resourceDirectory + "wallpiece.png");

    table.loadFromFile(resourceDirectory + "table.png");

    openDoor.loadFromFile(resourceDirectory + "opendoor.png");
    closeDoor.loadFromFile(resourceDirectory + "closedoor.png");

    shovel1.loadFromFile(resourceDirectory + "pelle1.png");
    shovel2.loadFromFile(resourceDirectory + "pelle2.png");
    shovel3.loadFromFile(resourceDirectory + "pelle3.png");

    socle.loadFromFile(resourceDirectory + "socle.png");
    TRex.loadFromFile(resourceDirectory + "trex.png");
}
