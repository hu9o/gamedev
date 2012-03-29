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
        void affiche(sf::RenderWindow& app);
        void move();

        bool gotoPos(sf::Vector2i pos);

    protected:
        sf::Image m_image;
        sf::Sprite m_sprite;

        std::vector<sf::Vector2i> m_movementStack;


        sf::Vector2f spritePos(sf::Vector2i v);
    private:
};

