#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Case.h"

// taille de l'affichage (à revoir?)
extern const int SCREEN_W, SCREEN_H;

class Entity;
class Character;

/**
  * Classe Map
  * Représente la carte, ensemble de cases.
  *
  * @param w largeur de la carte
  * @param h hauteur de la carte
  * @authr hu9o
  * @see Case
  */
class Map
{
    public:

        // Cteur, dteur
        Map(int w, int h);
        virtual ~Map();


        /// affiche les tiles sur une RenderWindow
        void affiche(sf::RenderWindow& app);

        /// ajoute une Entity à la Map, qui sera affichée en même temps que
        /// celle-ci
        void registerEntity(Entity& e);
        void registerCharacter(Character& c);

        /// handles mouse events
        void mouseDown(sf::Event evt);
        void mouseMove(sf::Event evt);

        /// la case est-elle traversable?
        bool isWalkable(int x, int y);

        std::vector<sf::Vector2i> findPath (sf::Vector2i sourcePos,
                                            sf::Vector2i targetPos);

        /**
          * Convertit du repère cartésien au repère isométrique
          * (modifie l'entrée, ne renvoie rien)
          *
          * @param v vecteur contenant les coordonnées (x, y)
          * @authr hu9o
          * @see fromIso()
          */
        void toIso(sf::Vector2f& v);

        /**
          * Inverse de la fonction Map::toIso()
          *
          * @param v vecteur contenant les coordonnées (x, y)
          * @authr hu9o
          * @see toIso()
          */
        void fromIso(sf::Vector2<float>& v);

        float getElapsedTime();

        void loadTest();

    protected:

    private:

        class Node
        {
            public:
            Node(Node* _p, int _x, int _y)
             : parent(_p), x(_x), y(_y)
            {
                if (parent != NULL)
                    target = parent->target;
                else
                    target = NULL;
            }
            int getF() { return g+getH(); }
            int getH()
            {
                return (target != NULL)? abs(x-target->x)+abs(y-target->y) : 0;
            }

            Node* parent;
            Node* target;
            int x, y;
            int g;
        };


        /// largeur et hauteur de la map
        const int m_w, m_h;

        Case*** m_map;
        sf::Texture m_tileset;
        sf::Texture m_Objs;

        sf::Sprite m_curs;
        sf::Texture m_cursImg;
        sf::Vector2i m_cursPos;

        sf::Clock m_clock;

        std::vector<Entity*> m_entities;
        Character* m_character;


        // MÉTHODES

        /// charge le tileset
        void loadTileset(std::string);

        void setCursorPos(sf::Vector2f v);
        sf::Vector2f getCursorPos();

};
