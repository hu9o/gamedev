#include "Case.h"

Case::Case(Map& map, int x, int y) :
    m_map(map),
    m_x(x),
    m_y(y)
{
    m_isObject = false;
    m_cost = 10;
    relativeObjectImagePos.x = 0;
    relativeObjectImagePos.y = 0;
}

Case::~Case()
{
    //dtor
}

void Case::setTex(sf::Texture* m_tile)
{
    m_terrain.setTexture(*m_tile);
    m_objet.setTexture(*m_tile);
}

void Case::setPos(float x, float y)
{
    m_pos.x = x;
    m_pos.y = y;

    m_terrain.setPosition(x, y);
    m_objet.setPosition(x + relativeObjectImagePos.x,
                        y + relativeObjectImagePos.y);
}

sf::Vector2i Case::getPos()
{
    return m_pos;
}

void Case::setRelativeObjectImagePos(int x, int y)
{
    relativeObjectImagePos.x = x * Case::WIDTH;
    relativeObjectImagePos.y = y * Case::HEIGHT;
}

void Case::setGround(int x, int y)
{
    // Zone du tileset à afficher
    m_terrain.setTextureRect(sf::IntRect(x*Case::WIDTH,
                                         y*Case::HEIGHT,
                                         Case::WIDTH,
                                         Case::HEIGHT));
}

void Case::setObject(int x, int y, int w, int h)
{
    // Zone du tileset à afficher
    m_objet.setTextureRect(sf::IntRect(x*Case::WIDTH,
                                       y*Case::HEIGHT,
                                       w*Case::WIDTH,
                                       h*Case::HEIGHT));

    m_isObject = true;
}

sf::Sprite Case::getTerrain()
{
    return m_terrain;
}

sf::Sprite Case::getObjet()
{
    return m_objet;
}

bool Case::hasObject()
{
    return m_isObject;
}

bool Case::isWalkable()
{
    return m_cost < 100;
}

int Case::getCost()
{
    return m_cost;
}

void Case::setCost(int cost)
{
    m_cost = cost;
}
