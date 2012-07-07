#include <SFML/Graphics.hpp>

#include "Map.h"
#include "NPC.h"

extern const int SCREEN_W = 800; // TODO: Mettre Ã§a dans une classe?
extern const int SCREEN_H = 600;

int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(SCREEN_W, SCREEN_H), "Projet Gamedev");
    App.setFramerateLimit(25);

    //Chargement de la map (à partir d'un fichier)
    Map carte("default-map");

    //Création du perso
    Character perso(carte);

    // Start the game loop
    while (App.isOpen())
    {
        // Process events
        sf::Event evt;
        while (App.pollEvent(evt))
        {
            // Close window : exit
            if (evt.type == sf::Event::Closed)
                App.close();

            if (evt.type == sf::Event::MouseButtonPressed)
                carte.mouseDown(evt);

            if (evt.type == sf::Event::MouseMoved)
                carte.mouseMove(evt);
        }

        // Clear screen
        App.clear();

        // Draw the sprite
        carte.affiche(App);

        // Update the window
        App.display();
    }

    return EXIT_SUCCESS;
}
