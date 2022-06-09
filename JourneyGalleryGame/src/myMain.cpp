
#include <stdio.h>
#include <assert.h>

#include "box2d/box2d.h"
#include <Player.cpp>
#include "Game.h"

int myMain()
{
    //Init game
    Game game;


    sf::Music music;
    //Merci Guitou le meilleur compositeur du monde 
    if (!music.openFromFile("resources/Music_DigDeeper.wav")) {
        return -1;
    }
    music.play();
    sf::Clock globalClock;
    while (game.running())
    {
        game.update();
        ImGui::SFML::Update(*game.get_window(), globalClock.restart());
        game.render();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
