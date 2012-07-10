#include <SFML/Graphics.hpp>

#include "Map.h"
#include "NPC.h"

extern const int SCREEN_W = 800; // TODO: Mettre รงa dans une classe?
extern const int SCREEN_H = 600;

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(SCREEN_W, SCREEN_H), "Projet Gamedev");
    app.setFramerateLimit(25);

    //Chargement de la map (เ partir d'un fichier)
    Map carte("default-map");

    // Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event evt;
        while (app.pollEvent(evt))
        {
            // Close window : exit
            if (evt.type == sf::Event::Closed)
                app.close();

            if (evt.type == sf::Event::MouseButtonPressed)
                carte.mouseDown(evt);

            if (evt.type == sf::Event::MouseMoved)
                carte.mouseMove(evt, app);
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        carte.affiche(app);
        carte.mouseMove(app);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
