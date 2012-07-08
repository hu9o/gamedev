#include "Case.h"
#include "Map.h"

Case::Case(Map& map, int x, int y) :
    m_map(map),
    m_pos(x, y),
    m_intpos(x, y)
{
    m_isObject = false;
    m_isClean = true;
    m_objectCost = 10;
    m_terrainCost = 10;
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

void Case::setClean(bool clean)
{
    m_isClean = clean;
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
    return getCost() < 100;
}

int Case::getCost()
{
    return m_terrainCost + m_objectCost;
}

void Case::setObjectCost(int cost)
{
    m_objectCost = cost;
}

void Case::setTerrainCost(int cost)
{
    m_terrainCost = cost;
}

bool Case::activate()
{
    bool test = false;
    std::cout << "active!" << std::endl;

    if (m_map.activateEntityAt(m_intpos) == NULL)
    {
        if(!m_isClean)
        {
            m_isObject = false;
            m_objectCost = 0;
            m_isClean = true;
            test = true;
        }
    }

    return test;
}

bool Case::isClean()
{
    return m_isClean;
}
