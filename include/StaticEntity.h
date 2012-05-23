#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Entity;

class StaticEntity : public Entity
{
    public:
        StaticEntity(Map& map);
        virtual ~StaticEntity();

        sf::Vector2i getPosition();
        void affiche(sf::RenderWindow& app);
        void setTileset(sf::Texture& tileset);
        void setPositionOnTileset(int x, int y,int w, int h, int centerX, int centerY);

    protected:
        sf::Sprite m_sprite;
        sf::Texture m_tileset;
        sf::Vector2i m_spriteOffset;

    private:
};
