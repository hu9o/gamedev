#pragma once

#include <SFML/Graphics.hpp>


class Map;

/**
  * Classe Case
  * Représente une case, contenue dans une Map.
  * Étend sf::Sprite, l'image correspondante est le tileset.
  *
  * @param map la carte dont elle fait partie
  * @param x sa position x sur la carte
  * @param y sa position y sur la carte
  * @authr hu9o
  * @see Map
  * @see sf::Sprite
  */
class Case : public sf::Sprite
{
    public:

        /// Constantes, largeur et hauteur d'une case (image) en pixels.
        static const int WIDTH = 48,
                         HEIGHT = 32;

        Case(Map& map, int x, int y);
        virtual ~Case();

        /// Donne la position de la case sur le tileset (et non sur la map)
        void setPositionOnTileset(int x, int y);
        bool isWalkable();

    protected:
        /// Carte parente
        Map& m_map;

        //TODO: Est-ce utile?
        /// Position sur la carte
        int m_x, m_y;

        /// Case franchissable?
        bool m_walkable;

    private:
};
