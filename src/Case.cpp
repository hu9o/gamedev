#include "Case.h"

Case::Case(Map& map, int x, int y) :
    m_map(map),
    m_x(x),
    m_y(y)
{
    m_walkable = true;
    m_object = false;
}

Case::~Case()
{
    //dtor
}

void Case::setTex(sf::Texture* m_tile)
{
    terrain.setTexture(*m_tile);
    objet.setTexture(*m_tile);
}

void Case::setPos(float x, float y)
{
    terrain.setPosition(x,y);
    objet.setPosition(x,y);
}

void Case::setGround(int x, int y)
{
    // Zone du tileset à afficher
    terrain.setTextureRect(sf::IntRect(x*Case::WIDTH,
                                       y*Case::HEIGHT,
                                       Case::WIDTH,
                                       Case::HEIGHT));
}

void Case::setObject(int x, int y)
{
    // Zone du tileset à afficher
    objet.setTextureRect(sf::IntRect(x*Case::WIDTH,
                                     y*Case::HEIGHT,
                                     Case::WIDTH,
                                     Case::HEIGHT));
    m_object = true;
}

sf::Sprite Case::getTerrain()
{
    return terrain;
}

sf::Sprite Case::getObjet()
{
    return objet;
}

bool Case::hasObject()
{
    return m_object;
}

bool Case::isWalkable()
{
    return m_walkable;
}

void Case::setWalkable(bool walk)
{
    m_walkable = walk;
}
