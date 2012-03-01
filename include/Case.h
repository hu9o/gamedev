#pragma once

#include <SFML/Graphics.hpp>

class Case : public sf::Sprite
{
    public:
        Case();
        virtual ~Case();

    protected:
        bool m_occupee;

    private:
};
