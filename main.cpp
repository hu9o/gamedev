#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Character.h"

extern const int SCREEN_W = 800; // TODO: Mettre ça dans une classe?
extern const int SCREEN_H = 600;

int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(SCREEN_W, SCREEN_H), "Projet Gamedev");
    App.SetFramerateLimit(25);

    // Load a sprite to display
    Map carte(16, 16);
    carte.loadTest();
    Character perso(carte);

    // Start the game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event evt;
        while (App.GetEvent(evt))
        {
            // Close window : exit
            if (evt.Type == sf::Event::Closed)
                App.Close();

            if (evt.Type == sf::Event::MouseButtonPressed)
                carte.mouseDown(evt);

            if (evt.Type == sf::Event::MouseMoved)
                carte.mouseMove(evt);
        }

        // Clear screen
        App.Clear();


        // Draw the sprite
        carte.affiche(App);

        // Update the window
        App.Display();
    }

    return EXIT_SUCCESS;
}
