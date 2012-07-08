#ifndef ENEMY_H
#define ENEMY_H

#include "NPC.h"

class Enemy : NPC
{
    public:
        Enemy(Map& map, sf::Vector2i pos, std::string name, int skin, std::string type);
        virtual ~Enemy();

        virtual void move();

    protected:
        std::string m_type;

    private:
};

#endif // ENEMY_H
