#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Entity.h"

class Map;

/**
  * Classe Character
  * Hérite de Entity, représente le personnage contrôlé par le joueur.
  *
  * @authr hu9o
  * @see Character
  * @see Map
  */
class Character : public Entity
{
    public:
        Character(Map& map);
        virtual ~Character();

        /// affiche le perso sur une RenderWindow
        void affiche(sf::RenderWindow& app, sf::Vector2f& pos);

        bool gotoPos(int x,  int y);

    protected:
        sf::Image m_image;
        sf::Sprite m_sprite;
    private:
};

