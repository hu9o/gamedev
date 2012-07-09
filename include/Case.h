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

        void affiche(sf::RenderWindow& app);

        void setTex(sf::Texture *tex);
        void setPos(float x, float y);
        sf::Vector2i getPos();

        /// Situe le terrain et l'objet de la case sur le tileset (et non sur la map)
        void setGround(int x, int y);
        void setObject(int x, int y, int w = 1, int h = 1);
        void setClean(bool clean);
        void setAutoTile(bool autoTile = true);

        sf::Sprite& getTerrain();
        sf::Sprite& getObjet();

        bool hasObject();
        bool isWalkable();
        int getCost();
        void setObjectCost(int cost);
        void setTerrainCost(int cost);

        void setRelativeObjectImagePos(int x, int y);

        bool activate();
        bool isClean();
        void setTrigger(bool val);
        bool isTriggered();

    protected:
        /// Carte parente
        Map& m_map;
        sf::Vector2i m_pos;
        sf::Vector2i m_intpos;

        /// Position sur la carte
        //int m_x, m_y;

        /// Coût de déplacement
        int m_terrainCost;
        int m_objectCost;

        /// Afficher l'objet?
        bool m_isObject;

        ///Pollué ou pas
        bool m_isClean;

        bool m_autoTile;

        sf::Vector2i relativeObjectImagePos;

        /// Sprites du terrain et de l'objet (éventuel)
        sf::Sprite m_terrain;
        sf::Sprite m_objet;

        sf::Texture* m_texture;

        bool m_triggerable;
        bool m_triggered;
};
