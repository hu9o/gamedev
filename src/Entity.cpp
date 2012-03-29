#include "Entity.h"

Entity::Entity(Map& map) : m_map(map)
{
    // perso sur la carte
    m_map.registerEntity(*this);
    m_pos.x = 0;
    m_pos.y = 0;
}

Entity::~Entity()
{
    //dtor
}

sf::Vector2i Entity::getPosition()
{
    return m_pos;
}

void Entity::setPosition(sf::Vector2i& pos)
{
    m_pos = pos;
}

void Entity::setPosition(int x, int y)
{
    m_pos.x = x;
    m_pos.y = y;
}
