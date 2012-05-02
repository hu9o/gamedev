#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "JSON.h"

class Tileset
{
    public:
        Tileset(std::string path);
        virtual ~Tileset();

        sf::Image getImage();
        sf::IntRect getTerrain(std::string name);

    protected:
    private:
        sf::Image img;
        JSON j;
};

