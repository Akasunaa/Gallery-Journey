
#include <stdio.h>
#include <assert.h>
#include <tmxlite/Map.hpp>

#include "box2d/box2d.h"
#include <Player.cpp>
#include "Game.h"

int myMain()
{
    //Init game
    Game game;


    sf::Clock globalClock;
    while (game.running())
    {
        game.update();
        game.render();
    }

    return 0;
}
