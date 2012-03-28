#include "Entity.h"

Entity::Entity(Map& map) : m_map(map)
{
    // perso sur la carte
    m_map.registerEntity(*this);
}

Entity::~Entity()
{
    //dtor
}

sf::Vector2<int> Entity::getPosition()
{
    return m_pos;
}

void Entity::setPosition(sf::Vector2<int>& pos)
{
    m_pos = pos;
}

void Entity::setPosition(int x, int y)
{
    m_pos.x = x;
    m_pos.y = y;
}
