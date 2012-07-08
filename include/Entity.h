#pragma once

#include <SFML/Graphics.hpp>
#include "Case.h"

class Map;
class Case;
class Character;

/**
  * Classe Entity
  * Classe abstraite dont héritent les entités, notamment Character.
  * Les Entity sont rattachées à une Map, et sont affichées lors de l'affichage
  * de cette Map.
  *
  * @author hu9o
  * @see Character
  * @see Map
  */
class Entity
{
    public:
        Entity(Map& map);
        virtual ~Entity();

        virtual void affiche(sf::RenderWindow& app) = 0;

        virtual sf::Vector2i getPosition();
        void setPosition(sf::Vector2i& pos);
        void setPosition(int x, int y);
        void setCase(Case& c);

        virtual sf::Vector2i getDisplayPos() = 0;

        bool operator<(Entity& e);

        virtual bool activate(Character& chara);

    protected:
        /// carte sur laquelle est l'entité
        Map& m_map;
        sf::Vector2i m_pos;
        Case* m_currentCase;
    private:
};

