#pragma once

#include <SFML/Graphics.hpp>


class Map;

/**
  * Classe Case
  * Représente une case, contenue dans une Map.
  *
  * @param map la carte dont elle fait partie
  * @authr hu9o
  * @see Map
  */
class Case : public sf::Sprite
{
    public:

        /// Constantes, largeur et hauteur d'une case (image) en pixels.
        static const int WIDTH = 48,
                         HEIGHT = 32;

        Case(Map& map);
        virtual ~Case();

    protected:
        /// Carte parente
        Map& m_map;
        /// Case franchissable?
        bool m_occupee;

    private:
};
