#include "Case.h"
#include "Map.h"

Case::Case(Map& map, int x, int y) :
    m_map(map),
    m_pos(x, y),
    m_intpos(x, y)
{
    m_isObject = false;
    m_isClean = true;
    m_objectCost = 10;
    m_terrainCost = 10;
    relativeObjectImagePos.x = 0;
    relativeObjectImagePos.y = 0;
    m_autoTile = false;
    m_triggerable = false;
    m_triggered = false;
}

Case::~Case()
{
    //dtor
}


void Case::affiche(sf::RenderWindow& app)
{
    app.draw(getTerrain());

    if(hasObject())
    {
        if (!m_autoTile && !m_triggerable)
        {
            app.draw(getObjet());
        }
        else if (m_triggerable)
        {
            sf::IntRect r = m_objet.getTextureRect();
            sf::IntRect s = m_objet.getTextureRect();
            r.top += (m_triggered)? 0 : Case::HEIGHT;
            m_objet.setTextureRect(r);
            app.draw(m_objet);
            m_objet.setTextureRect(s);
        }
        else if (m_autoTile)
        {
            sf::Sprite plop(*m_texture);
            sf::IntRect r(0*Case::WIDTH + Case::WIDTH/2,
                                 5*Case::HEIGHT + Case::HEIGHT/2,
                                 Case::WIDTH/2,
                                 Case::HEIGHT/2);

            sf::Vector2i& pos = m_pos;

            bool test = true;

            bool top = test && m_map.getCaseAt(m_intpos.x, m_intpos.y-1)->isClean();
            bool bottom = test && m_map.getCaseAt(m_intpos.x, m_intpos.y+1)->isClean();
            bool left = test && m_map.getCaseAt(m_intpos.x-1, m_intpos.y)->isClean();
            bool right = test && m_map.getCaseAt(m_intpos.x+1, m_intpos.y)->isClean();

            plop.setTextureRect(sf::IntRect(r.left - (left? Case::WIDTH/2 : 0), r.top - (top? Case::HEIGHT/2 : 0), r.width, r.height));
            plop.setPosition(pos.x + 12, pos.y);
            app.draw(plop);


            plop.setTextureRect(sf::IntRect(r.left + (right? Case::WIDTH/2 : 0), r.top + (bottom? Case::HEIGHT/2 : 0), r.width, r.height));
            plop.setPosition(pos.x + 12, pos.y + 16);
            app.draw(plop);


            plop.setTextureRect(sf::IntRect(r.left - (left? Case::WIDTH/2 : 0), r.top + (bottom? Case::HEIGHT/2 : 0), r.width, r.height));
            plop.setPosition(pos.x, pos.y + 8);
            app.draw(plop);


            plop.setTextureRect(sf::IntRect(r.left + (right? Case::WIDTH/2 : 0), r.top - (top? Case::HEIGHT/2 : 0), r.width, r.height));
            plop.setPosition(pos.x+24, pos.y + 8);
            app.draw(plop);

        }
    }
}

void Case::setTex(sf::Texture* tex)
{
    m_texture = tex;
    m_terrain.setTexture(*tex);
    m_objet.setTexture(*tex);
}

void Case::setAutoTile(bool autoTile)
{
    m_autoTile = autoTile;
}

void Case::setPos(float x, float y)
{
    m_pos.x = x;
    m_pos.y = y;

    m_terrain.setPosition(x, y);
    m_objet.setPosition(x + relativeObjectImagePos.x,
                        y + relativeObjectImagePos.y);
}

void Case::setClean(bool clean)
{
    m_isClean = clean;
}

sf::Vector2i Case::getPos()
{
    return m_pos;
}

void Case::setRelativeObjectImagePos(int x, int y)
{
    relativeObjectImagePos.x = x * Case::WIDTH;
    relativeObjectImagePos.y = y * Case::HEIGHT;
}

void Case::setGround(int x, int y)
{
    // Zone du tileset à afficher
    m_terrain.setTextureRect(sf::IntRect(x*Case::WIDTH,
                                         y*Case::HEIGHT,
                                         Case::WIDTH,
                                         Case::HEIGHT));
}

void Case::setObject(int x, int y, int w, int h)
{
    // Zone du tileset à afficher
    m_objet.setTextureRect(sf::IntRect(x*Case::WIDTH,
                                       y*Case::HEIGHT,
                                       w*Case::WIDTH,
                                       h*Case::HEIGHT));

    m_isObject = true;
}

sf::Sprite& Case::getTerrain()
{
    return m_terrain;
}

sf::Sprite& Case::getObjet()
{
    return m_objet;
}

bool Case::hasObject()
{
    return m_isObject;
}

bool Case::isWalkable()
{
    return getCost() < 100;
}

int Case::getCost()
{
    return m_terrainCost + m_objectCost;
}

void Case::setObjectCost(int cost)
{
    m_objectCost = cost;
}

void Case::setTerrainCost(int cost)
{
    m_terrainCost = cost;
}

bool Case::activate()
{
    bool actionPerformed = false;
    std::cout << "active!" << std::endl;

    if (m_map.activateEntityAt(m_intpos) == NULL)
    {
        if(!m_isClean)
        {
            m_isObject = false;
            m_objectCost = 0;
            m_isClean = true;
            actionPerformed = true;
        }

        if(m_triggerable)
        {
            m_triggered = !m_triggered;
            std::cout << (m_triggered? "flip":"flop") << std::endl;
        }
    }

    return actionPerformed;
}

bool Case::isClean()
{
    return m_isClean;
}

void Case::setTrigger(bool val)
{
    m_triggerable = val;
}

bool Case::isTriggered()
{
    return m_triggered;
}
