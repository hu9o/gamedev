#include "StaticEntity.h"

StaticEntity::StaticEntity(Map& map) : Entity(map), m_spriteOffset(0, 0)
{
    //ctor
}

StaticEntity::~StaticEntity()
{
    //dtor
}

void StaticEntity::affiche(sf::RenderWindow& app)
{
    sf::Vector2i posInt = getPosition();

    m_sprite.setPosition(posInt.x, posInt.y);

    app.draw(m_sprite);
}

void StaticEntity::setTileset(sf::Texture& tileset)
{
    m_tileset = tileset;
    m_sprite.setTexture(m_tileset);
}

sf::Vector2i StaticEntity::getPosition()
{
    if (m_currentCase != NULL)
    {
        sf::Vector2i pos = m_currentCase->getPos();
        return sf::Vector2i(pos.x + m_spriteOffset.x, pos.y + m_spriteOffset.y);
    }
    else
    {
        return m_pos;
    }
}

void StaticEntity::setPositionOnTileset(int x, int y,int w, int h, int centerX, int centerY)
{
    m_sprite.setTextureRect(sf::IntRect(x*Case::WIDTH,
                                         y*Case::HEIGHT,
                                         w*Case::WIDTH,
                                         h*Case::HEIGHT));

    m_spriteOffset.x = -centerX * Case::WIDTH;
    m_spriteOffset.y = -centerY * Case::HEIGHT;
}
