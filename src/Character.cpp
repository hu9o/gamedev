#include "Character.h"
#include "Map.h"
#include <sstream>

Character::Character(Map& map) : Entity(map)
{
    // charge image
    if (!m_image.loadFromFile("gfx/charset.png"))
    {
        //TODO: Utiliser une exception?
        std::cerr << "Le chargement du tileset a échoué" << std::endl;
    }
    m_sprite.setTexture(m_image);
    m_map.registerCharacter(*this);

    m_sprite.setPosition(spritePos(m_pos));
    m_dir = 2;
    m_moving = false;
    m_speed = 1.8;
    m_skin = 0;
    m_exp = 0;
    m_maxExp = 100;
    m_lvl = 1;

    m_caseToActivate = NULL;
}

Character::~Character()
{
    //dtor
}

void Character::affiche(sf::RenderWindow& app)
{
    int imgNb = m_moving? (int)(m_map.getElapsedTime() * m_speed*5) % 2 : 0;


    m_sprite.setTextureRect(sf::IntRect(imgNb*32 + (m_skin%16)*64,
                                        m_dir*32 + (m_skin/16)*128,
                                        32,
                                        32));

    //m_sprite.SetPosition(pos);
    app.draw(m_sprite);
}

void Character::setPosition(sf::Vector2i pos)
{
    m_pos = pos;

    m_sprite.setPosition(spritePos(m_pos));
}

bool Character::gotoPos(sf::Vector2i pos, bool add, bool skipLast)
{

    // la position de départ est la position actuelle,
    // ou la prochaine sur la liste de mouvement s'il y en a une,
    // car le perso va finir son mouvement
    sf::Vector2i startPos = m_movementQueue.empty()?
                                            m_pos : *(m_movementQueue.end()-1);

    std::vector<sf::Vector2i> movementList = m_map.findPath(startPos, pos, skipLast);


    if (movementList.empty())
        return false;

    // s'il reste des élément, on en laisse un pourque le personnage
    // puisse finir son mouvement
    if (!m_movementQueue.empty())
    {
        sf::Vector2i last = *(m_movementQueue.end()-1);
        m_movementQueue.clear();
        m_movementQueue.push_front(last);
    }
    else
        m_movementQueue.clear();

    m_caseToActivate = skipLast? m_map.getCaseAt(movementList[0]) : NULL;

    // on ignore la première position, qui est la position actuelle
    //movementList.pop_back();
    while (movementList.size() > skipLast? 1 : 0)
    {
        m_movementQueue.push_front(*(movementList.end() - 1));
        movementList.pop_back();
    }

    return !m_movementQueue.empty();
}

bool Character::goInFrontOfPos(sf::Vector2i pos, bool add)
{
    return gotoPos(pos, add, true);
}

void Character::move()
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

        //if (d > speed*2) m_dir = (int)round((a + M_PI*2) / M_PI_4) % 8;
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

        if (m_movementQueue.empty())
        {
            std::cout << "fin du mouvement!" << std::endl;

            if (m_caseToActivate != NULL)
            {
                std::stringstream ss;
                ss << "+10px";

                m_exp += 10;

                if (m_exp >= m_maxExp)
                {
                    m_maxExp *= 1.2;
                    m_exp = 0;
                    m_lvl++;

                    ss << " : LEVEL UP!";
                }

                //m_map.display(ss.str());
            }
        }
    }
}

sf::Vector2f Character::spritePos(sf::Vector2i v)
{
    sf::Vector2f v2(v.x, v.y);
    m_map.toIso(v2);
    v2.x += 8;
    v2.y -= 13;
    return v2;
}

sf::Vector2i Character::getDisplayPos()
{
    return sf::Vector2i(m_sprite.getPosition().x, m_sprite.getPosition().y);
}

int Character::getExp()
{
    return m_exp;
}
int Character::getMaxExp()
{
    return m_maxExp;
}

int Character::getLevel()
{
    return m_lvl;
}


void Character::activateAt(sf::Vector2i pos)
{
    Case* c = m_map.getCaseAt(pos);

    if (c != NULL)
    {
        lookAt(pos);
        c->activate();
    }
}

void Character::lookAt(sf::Vector2i pos)
{
    float a = std::atan2(m_pos.y - pos.y, m_pos.x - pos.x);

    m_dir = (int)(round((a + M_PI*2 + 7*M_PI/4) / M_PI_2)) % 4;
}

