#include <SFML/Graphics.hpp>

#include "Map.h"

extern const int SCREEN_W = 800; // TODO: Mettre ça dans une classe?
extern const int SCREEN_H = 600;

int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(SCREEN_W, SCREEN_H), "pROJET gAMEDEV");
    App.SetFramerateLimit(25);

    // Load a sprite to display
    Map carte(6, 6);

	// Start the game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
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
