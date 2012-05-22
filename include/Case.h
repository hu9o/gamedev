#pragma once

#include <SFML/Graphics.hpp>

class Map;

/**
  * Classe Case
  * Représente une case, contenue dans une Map.
  *
  * @param map la carte dont elle fait partie
  * @param x sa position x sur la carte
  * @param y sa position y sur la carte
  * @authr hu9o
  * @see Map
  * @see sf::Sprite
  */

class Case
{
    public:

        /// Constantes, largeur et hauteur d'une case (image) en pixels.
        static const int WIDTH = 48,
                         HEIGHT = 32;

        Case(Map& map, int x, int y);
        virtual ~Case();

        void setTex(sf::Texture *m_tile);
        void setPos(float x, float y);

        /// Situe le terrain et l'objet de la case sur le tileset (et non sur la map)
        void setGround(int x, int y);
        void setObject(int x, int y);

        sf::Sprite getTerrain();
        sf::Sprite getObjet();

        bool hasObject();
        bool isWalkable();
        void setWalkable(bool walk);

    protected:
        /// Carte parente
        Map& m_map;

        /// Position sur la carte
        int m_x, m_y;

        /// Case franchissable?
        bool m_walkable;

        bool m_object;

    private:
        sf::Sprite terrain;
        sf::Sprite objet;
};
