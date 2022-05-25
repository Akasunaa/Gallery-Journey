#include "myMain.h"
#include <SFML/Graphics.hpp>


int myMain()
{


    //-------------affichage graphique
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(800, 800));
    window.setView(view);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Red);

        window.display();


    }
    return 0;



}