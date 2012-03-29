#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"

class Map;

/**
  * Classe Entity
  * Classe abstraite dont héritent les entités, notamment Character.
  * Les Entity sont rattachées à une Map, et sont affichées lors de l'affichage
  * de cette Map.
  *
  * @authr hu9o
  * @see Character
  * @see Map
  */
class Entity
{
    public:
        Entity(Map& map);
        virtual ~Entity();

        virtual void affiche(sf::RenderWindow& app) = 0;

        sf::Vector2i getPosition();
        void setPosition(sf::Vector2i& pos);
        void setPosition(int x, int y);

    protected:
        /// carte sur laquelle est le perso
        Map& m_map;
        sf::Vector2i m_pos;
    private:
};

