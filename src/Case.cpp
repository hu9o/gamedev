#include "Case.h"

#include <SFML/Graphics.hpp>

Case::Case(Map& map, int x, int y) :
    m_map(map),
    m_x(x),
    m_y(y)
{
    m_walkable = true;
}

Case::~Case()
{
    //dtor
}

void Case::setPositionOnTileset(int x, int y)
{
    // Zone du tileset à afficher
    setTextureRect(sf::IntRect(x*Case::WIDTH,
                           y*Case::HEIGHT,
                           (x+1)*Case::WIDTH,
                           (y+1)*Case::HEIGHT));

    ////TODO: C'EST DU TEST!
    //if (x == 1) m_walkable = false;
}

bool Case::isWalkable()
{
    return m_walkable;
}
