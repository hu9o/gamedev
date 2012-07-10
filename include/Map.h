#pragma once

#include <cmath>
#include <iostream>
#include <list>
#include <vector>
#include "Entity.h"
#include "Case.h"
#include "NPC.h"

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
  * @author hu9o
  * @see Case
  */
class Map
{
    public:

        // Cteur, dteur
        //Map(int w, int h);
        Map(std::string nom);
        virtual ~Map();


        /// affiche les tiles sur une RenderWindow
        void affiche(sf::RenderWindow& app);

        /// ajoute une Entity à la Map, qui sera affichée en même temps que
        /// celle-ci
        void registerEntity(Entity& e);
        void registerCharacter(Character& c);

        /// handles mouse events
        void mouseDown(sf::Event evt);
        void mouseMove(sf::Event evt, sf::RenderWindow& app);
        void mouseMove(sf::RenderWindow& app);

        /// la case est-elle traversable?
        bool isWalkable(int x, int y);

        std::vector<sf::Vector2i> findPath (sf::Vector2i sourcePos,
                                            sf::Vector2i targetPos,
                                            bool skipLast = false);

        /**
          * Convertit du repère cartésien au repère isométrique
          * (modifie l'entrée, ne renvoie rien)
          *
          * @param v vecteur contenant les coordonnées (x, y)
          * @author hu9o
          * @see fromIso()
          */
        void toIso(sf::Vector2f& v);

        /**
          * Inverse de la fonction Map::toIso()
          *
          * @param v vecteur contenant les coordonnées (x, y)
          * @author hu9o
          * @see toIso()
          */
        void fromIso(sf::Vector2<float>& v);

        float getElapsedTime();

        void loadTest();

        bool withinBounds(int x, int y);
        Case* getCaseAt(int x, int y);
        Case* getCaseAt(sf::Vector2i& v);

        void reorderEntities();

        Entity* getEntityAt(sf::Vector2i pos);
        Entity* activateEntityAt(sf::Vector2i pos);
        void say(NPC& npc, std::string msg);
        void display(std::string msg);

    protected:

    private:

        /// Structure uniquement utilisée par la fonction 'findPath'
        struct Node
        {
            Node(Node* _p, int _x, int _y, Case* _c)
             : parent(_p), x(_x), y(_y), c(_c)
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
            Case* c;
            int g;
            int cost;
        };

        struct MessageBox
        {
            MessageBox(Map& map) : m_map(map)
            {
                 m_counter = 0;
            }

            void show(std::string msg)
            {
                m_counter = 68;
                 m_text.setString(msg);
                 m_text.setPosition(10, 10);
                 m_text.setFont(m_font);
                 m_text.setCharacterSize(16);

                 std::cout << "AFFICHE!" << std::endl;
            }

            void display(sf::RenderWindow& app)
            {
                 // Draw it
                 if (m_counter > 0)
                 {
                     if (m_counter < 64)
                     {
                         m_text.setPosition(10, 10 - (m_counter < 54? (m_counter < 5? 5-m_counter : 0 )*2 : m_counter-54)*3);
                        app.draw(m_text);
                     }
                    m_counter--;
                }
            }

            void setFont(sf::Font font)
            {
                m_font = font;
            }

            sf::Font m_font;
            sf::Text m_text;
            int m_counter;
            Map& m_map;
        };


        /// largeur et hauteur de la map
        int m_w, m_h;

        Case*** m_map;
        sf::Texture m_tileset;

        MessageBox m_messageBox;


        sf::Sprite m_curs;
        sf::Texture m_cursImg;
        sf::Vector2i m_cursPos;
        sf::Vector2f m_cursRealPos;

        ///Je sais, c'est moche, mais j'ai pas osé créer une classe
        sf::Texture m_expBarTex;
        sf::Sprite m_expBarBorder;
        sf::Sprite m_expBarFill;
        sf::Text m_expBarLevelText;
        int m_expBarVal;

        sf::Sprite m_lifeBarBorder;
        sf::Sprite m_lifeBarFill;
        sf::Text m_lifeBarLevelText;
        int m_lifeBarVal;

        sf::Clock m_clock;

        std::list<Entity*> m_entities;
        Character* m_character;

        sf::Font m_font;
        sf::View m_mapView;

        // MÉTHODES

        /// charge le tileset
        void loadTileset(std::string);
        void initHUD();

        void setCursorPos(sf::Vector2f v);
        sf::Vector2f getCursorPos();


};
