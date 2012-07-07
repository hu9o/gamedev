#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include "Entity.h"

class Map;

enum Direction { DIR_UPLEFT, DIR_UPRIGHT, DIR_DOWNLEFT, DIR_DOWNRIGHT };

/**
  * Classe Character
  * Hérite de Entity, représente le personnage contrôlé par le joueur.
  *
  * @author hu9o
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

<<<<<<< HEAD
        bool gotoPos(sf::Vector2i pos, bool add, bool skipLast = false);
        bool goInFrontOfPos(sf::Vector2i pos, bool add);
        void setPosition(sf::Vector2i pos);
=======
        bool gotoPos(sf::Vector2i pos, bool add);
        void plant(sf::Vector2i pos, bool add);
>>>>>>> 42461bb6d6e0f3630aa219cda2055d18d097ea86

        sf::Vector2i getDisplayPos();
        void activate(sf::Vector2i pos);

    protected:
        sf::Texture m_image;
        sf::Sprite m_sprite;

        Case* m_caseToActivate;

        float m_speed;
        int m_dir; // remplacer par une enum?
        int m_skin;
        bool m_moving;

        std::deque<sf::Vector2i> m_movementQueue;


        sf::Vector2f spritePos(sf::Vector2i v);
    private:
};

