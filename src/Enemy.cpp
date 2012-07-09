#include "Enemy.h"
#include "Map.h"

Enemy::Enemy(Map& map, sf::Vector2i pos, std::string name, int skin, std::string type) :
    NPC(map, pos, name, skin),
    m_type(type)
{

}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::move()
{
    m_moving = !m_movementQueue.empty();

    if (!m_movementQueue.empty())
    {
        sf::Vector2i nextPos = *(m_movementQueue.end() - 1);
        sf::Vector2f curIsoPos, nextIsoPos, v;

        curIsoPos = m_sprite.getPosition();

        nextIsoPos = spritePos(nextPos);


        sf::Vector2f curPos = curIsoPos;
        m_map.fromIso(curPos);
        Case* curCase = m_map.getCaseAt(ceil(curPos.x), ceil(curPos.y));

        float speed = m_speed * 10 / curCase->getCost();


        v.x = nextIsoPos.x - curIsoPos.x;
        v.y = nextIsoPos.y - curIsoPos.y;

        float a = std::atan2(v.y, v.x);
        float d = std::sqrt(v.x*v.x + v.y*v.y);        // en polaire

        if (d > speed*2) m_dir = (int)(round((a + M_PI*2) / M_PI_2) + 1) % 4;

        //TODO: utiliser 'a' pour donner la bonne valeur à m_dir (direction)

        v.x = std::cos(a) * speed;                // retour en cartésien
        v.y = std::sin(a) * speed;

        m_sprite.setPosition(curIsoPos.x + v.x, curIsoPos.y + v.y);

        if (d < speed)
        {
            m_pos = nextPos;
            m_sprite.setPosition(nextIsoPos);
            m_movementQueue.pop_back();
        }
    }
    else
    {
        sf::Vector2i nextPos;

        int nbWalkables = 0;

        for (int i=-1; i<=1; i++)
        {
            for (int j=-1; j<=1; j++)
            {
                int x = m_pos.x+i;
                int y = m_pos.y+j;

                if (m_map.isWalkable(x, y)
                    && (m_type != "scum" || !m_map.getCaseAt(x, y)->isClean())
                    && (i || j)
                    && (!i || !j || (m_map.isWalkable(m_pos.x, y) && (m_type != "scum" || !m_map.getCaseAt(m_pos.x, y)->isClean())
                                     && m_map.isWalkable(x, m_pos.y) && (m_type != "scum" || !m_map.getCaseAt(x, m_pos.y)->isClean())
                                     )
                        )
                   )
                    nbWalkables++;
            }
        }

        nbWalkables = std::rand() % (nbWalkables+1);

        for (int i=-1; i<=1; i++)
        {
            for (int j=-1; j<=1; j++)
            {
                int x = m_pos.x+i;
                int y = m_pos.y+j;

                if (m_map.isWalkable(x, y)
                    && (m_type != "scum" || !m_map.getCaseAt(x, y)->isClean())
                    && (i || j)
                    && (!i || !j || (m_map.isWalkable(m_pos.x, y) && (m_type != "scum" || !m_map.getCaseAt(m_pos.x, y)->isClean())
                                     && m_map.isWalkable(x, m_pos.y) && (m_type != "scum" || !m_map.getCaseAt(x, m_pos.y)->isClean())
                                     )
                        )
                   )
                {
                    nbWalkables--;

                    if (!nbWalkables)
                    {
                        nextPos.x = m_pos.x+i;
                        nextPos.y = m_pos.y+j;
                        m_movementQueue.push_back(nextPos);
                        return;
                    }
                }
            }
        }

    }
}
