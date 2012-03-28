#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Case.h"

// taille de l'affichage (à revoir?)
extern const int SCREEN_W, SCREEN_H;

class Entity;

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

        /// handles click events
        void click(sf::Event evt);


    protected:

    private:

        /// largeur et hauteur de la map
        const int m_w, m_h;

        Case*** m_map;
        sf::Image m_tileset;

        std::vector<Entity*> m_entities;


        // MÉTHODES

        /// charge le tileset
        void loadTileset(std::string);

        /**
          * Convertit du repère cartésien au repère isométrique
          * (modifie l'entrée, ne renvoie rien)
          *
          * @param v vecteur contenant les coordonnées (x, y)
          * @authr hu9o
          * @see fromIso()
          */
        void toIso(sf::Vector2<float>& v);

        /**
          * Inverse de la fonction Map::toIso()
          *
          * @param v vecteur contenant les coordonnées (x, y)
          * @authr hu9o
          * @see toIso()
          */
        void fromIso(sf::Vector2<float>& v);

};
