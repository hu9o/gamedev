#pragma once

#include "Character.h"

class NPC : public Character
{
    public:
        NPC(Map& map, sf::Vector2i pos, std::string name, int skin);
        virtual ~NPC();

        void addMessage(std::string msg);

        virtual bool activate(Character& chara);

        std::string getName();

    protected:
        std::vector<std::string> m_messages;
        unsigned int m_messageNb;
        std::string m_name;

    private:
};

