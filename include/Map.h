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
        Map(int w, int h);
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

        Entity* activateEntityAt(sf::Vector2i pos);
        void say(NPC& npc, std::string msg);

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
            MessageBox()
            {
                 m_font.loadFromFile("fonts/minecraftia.ttf");
                 m_text = NULL;
                 m_counter = 0;
            }

            void show(std::string msg)
            {
                 // Create a text
                 if (m_text != NULL)
                    delete m_text;

                m_counter = 48;

                 m_text = new sf::Text(msg);
                 m_text->setPosition(10, 10);
                 m_text->setFont(m_font);
                 m_text->setCharacterSize(16);

                 std::cout << "AFFICHE!" << std::endl;
            }

            void display(sf::RenderWindow& app)
            {
                 // Draw it
                 if (m_counter > 0)
                 {
                     if (m_counter < 44 && m_text != NULL)
                     {
                        app.draw(*m_text);
                     }
                    m_counter--;
                }
            }


            sf::Font m_font;
            sf::Text* m_text;
            int m_counter;
        };

        MessageBox m_messageBox;

        /// largeur et hauteur de la map
        int m_w, m_h;

        Case*** m_map;
        sf::Texture m_tileset;

        sf::Sprite m_curs;
        sf::Texture m_cursImg;
        sf::Vector2i m_cursPos;

        sf::Clock m_clock;

        std::list<Entity*> m_entities;
        Character* m_character;


        // MÉTHODES

        /// charge le tileset
        void loadTileset(std::string);

        void setCursorPos(sf::Vector2f v);
        sf::Vector2f getCursorPos();


};
