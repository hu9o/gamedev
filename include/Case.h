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
  * @author hu9o
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
        sf::Vector2i getPos();

        /// Situe le terrain et l'objet de la case sur le tileset (et non sur la map)
        void setGround(int x, int y);
        void setObject(int x, int y, int w = 1, int h = 1);

        sf::Sprite getTerrain();
        sf::Sprite getObjet();

        bool hasObject();
        bool isWalkable();
        int getCost();
        void setCost(int cost);

        void setRelativeObjectImagePos(int x, int y);

    protected:
        /// Carte parente
        Map& m_map;
        sf::Vector2i m_pos;

        /// Position sur la carte
        int m_x, m_y;

        /// Coût de déplacement
        int m_cost;

        /// Afficher l'objet?
        bool m_isObject;

        sf::Vector2i relativeObjectImagePos;

        /// Sprites du terrai et de l'objet (éventuel)
        sf::Sprite m_terrain;
        sf::Sprite m_objet;
};
