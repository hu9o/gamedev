#include "Entity.h"

Entity::Entity(Map& map) : m_map(map), m_currentCase(NULL)
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
    //m_map.reorderEntities();
}

void Entity::setPosition(int x, int y)
{
    m_pos.x = x;
    m_pos.y = y;
    m_map.reorderEntities();
}

void Entity::setCase(Case& c)
{
    m_currentCase = &c;
}

bool Entity::operator<(Entity& e)
{
    return getDisplayPos().y < e.getDisplayPos().y;
}
