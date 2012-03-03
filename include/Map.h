#pragma once

#include <cmath>
#include <iostream>
#include "Case.h"

class Map
{
    public:
        Map(int w, int h);
        virtual ~Map();

        void affiche(sf::RenderWindow& app);

    protected:
    private:
        Case*** m_map;
        sf::Image m_tileset;

        int m_w, m_h;

        void loadTileset(std::string);

        void toIso(sf::Vector2<float>& v);
        void fromIso(sf::Vector2<float>& v);
};
