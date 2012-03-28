#include "Character.h"

Character::Character(Map& map) : Entity(map)
{
    // charge image
    if (!m_image.LoadFromFile("gfx/char.png"))
    {
        //TODO: Utiliser une exception?
        std::cerr << "Le chargement du tileset a échoué" << std::endl;
    }
    m_image.SetSmooth(false);
    m_sprite.SetImage(m_image);
}

Character::~Character()
{
    //dtor
}

void Character::affiche(sf::RenderWindow& app, sf::Vector2<float>& pos)
{
    m_sprite.SetPosition(pos);
    app.Draw(m_sprite);
}
