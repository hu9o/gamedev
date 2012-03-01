#include <SFML/Graphics.hpp>

#include "Map.h"

int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    Map carte(4, 4);

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

        sf::Sleep(0.04);
    }

    return EXIT_SUCCESS;
}
