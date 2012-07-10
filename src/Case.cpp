#include "Case.h"
#include "Map.h"
#include "Character.h"

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

    if (true)
    {
        sf::Sprite corner(*m_texture);

        sf::IntRect r(Case::WIDTH, Case::HEIGHT, Case::WIDTH/2, Case::HEIGHT/2);
        corner.setTextureRect(r);

        Case* ctop = m_map.getCaseAt(m_intpos.x, m_intpos.y-1);
        Case* cbottom = m_map.getCaseAt(m_intpos.x, m_intpos.y+1);
        Case* cleft = m_map.getCaseAt(m_intpos.x-1, m_intpos.y);
        Case* cright = m_map.getCaseAt(m_intpos.x+1, m_intpos.y);
        Case* ctopleft = m_map.getCaseAt(m_intpos.x-1, m_intpos.y-1);
        Case* ctopright = m_map.getCaseAt(m_intpos.x+1, m_intpos.y-1);
        Case* cbottomleft = m_map.getCaseAt(m_intpos.x-1, m_intpos.y+1);
        Case* cbottomright = m_map.getCaseAt(m_intpos.x+1, m_intpos.y+1);

        std::string top = ctop? ctop->getTerrainName() : "";
        std::string bottom = cbottom? cbottom->getTerrainName() : "";
        std::string left = cleft? cleft->getTerrainName() : "";
        std::string right = cright? cright->getTerrainName() : "";

        if (top != "" && top != m_terrainName && top == left && (!ctopleft || ctopleft->getTerrainName() != m_terrainName))
        {
            r.left = ctop->getTerrain().getTextureRect().left;
            r.top = ctop->getTerrain().getTextureRect().top + Case::HEIGHT;

            corner.setPosition(m_pos.x + Case::WIDTH/4, m_pos.y);

            corner.setTextureRect(r);
            app.draw(corner);
        }

        if (top != "" && top != m_terrainName && top == right && (!ctopright || ctopright->getTerrainName() != m_terrainName))
        {
            r.left = ctop->getTerrain().getTextureRect().left + Case::WIDTH/2;
            r.top = ctop->getTerrain().getTextureRect().top + Case::HEIGHT;

            corner.setPosition(m_pos.x + Case::WIDTH/2, m_pos.y + Case::HEIGHT/4);

            corner.setTextureRect(r);
            app.draw(corner);
        }

        if (bottom != "" && bottom != m_terrainName && bottom == left && (!cbottomleft || cbottomleft->getTerrainName() != m_terrainName))
        {
            r.left = cbottom->getTerrain().getTextureRect().left;
            r.top = cbottom->getTerrain().getTextureRect().top + Case::HEIGHT + Case::HEIGHT/2;

            corner.setPosition(m_pos.x, m_pos.y + Case::HEIGHT/4);

            corner.setTextureRect(r);
            app.draw(corner);
        }

        if (bottom != "" && bottom != m_terrainName && bottom == right && (!cbottomright || cbottomright->getTerrainName() != m_terrainName))
        {
            r.left = cbottom->getTerrain().getTextureRect().left + Case::WIDTH/2;
            r.top = cbottom->getTerrain().getTextureRect().top + Case::HEIGHT + Case::HEIGHT/2;

            corner.setPosition(m_pos.x + Case::WIDTH/4, m_pos.y + Case::HEIGHT/2);

            corner.setTextureRect(r);
            app.draw(corner);
        }
    }

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


            sf::IntRect r = m_objet.getTextureRect();
            r.left += Case::WIDTH/2;
            r.top += Case::HEIGHT/2;
            r.width = Case::WIDTH/2;
            r.height = Case::HEIGHT/2;

            sf::Vector2i& pos = m_pos;

            bool test = true;

            bool top = test && !m_map.getCaseAt(m_intpos.x, m_intpos.y-1)->hasObject(m_objName);
            bool bottom = test && !m_map.getCaseAt(m_intpos.x, m_intpos.y+1)->hasObject(m_objName);
            bool left = test && !m_map.getCaseAt(m_intpos.x-1, m_intpos.y)->hasObject(m_objName);
            bool right = test && !m_map.getCaseAt(m_intpos.x+1, m_intpos.y)->hasObject(m_objName);

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

void Case::setGround(int x, int y, std::string name)
{
    m_terrainName = name;

    // Zone du tileset à afficher
    m_terrain.setTextureRect(sf::IntRect(x*Case::WIDTH,
                                         y*Case::HEIGHT,
                                         Case::WIDTH,
                                         Case::HEIGHT));
}

void Case::setObject(std::string name, int x, int y, int w, int h)
{
    m_objName = name;

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

bool Case::hasObject(std::string& name)
{
    return m_objName == name;
}

std::string Case::getTerrainName()
{
    return m_terrainName;
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

bool Case::activate(Character& chara)
{
    bool actionPerformed = false;
    std::cout << "active!" << std::endl;

    if (m_map.activateEntityAt(m_intpos) == NULL)
    {
        if(!m_isClean)
        {
            m_isObject = false;
            m_objName = "";
            m_objectCost = 0;
            m_isClean = true;
            actionPerformed = true;

            chara.earnXP(10);
        }

        if(m_triggerable)
        {
            m_triggered = !m_triggered;
            std::cout << (m_triggered? "flip":"flop") << std::endl;
            actionPerformed = true;
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
