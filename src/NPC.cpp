#include "NPC.h"
#include "Map.h"

NPC::NPC(Map& map, sf::Vector2i pos, std::string name, int skin) : Character(map), m_name(name)
{
    setPosition(pos);
    m_skin = skin;
    m_messageNb = 0;
}

NPC::~NPC()
{
    //dtor
}

void NPC::addMessage(std::string msg)
{
    m_messages.push_back(msg);
}

bool NPC::activate()
{
    if (m_messages.size() > m_messageNb)
    {
        m_map.say(*this, m_messages[m_messageNb]);

        if (m_messages.size() > m_messageNb + 1)
            m_messageNb++;

        return true;
    }

    return false;
}

std::string NPC::getName()
{
    return m_name;
}
