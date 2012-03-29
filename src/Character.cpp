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
    m_map.registerCharacter(*this);
}

Character::~Character()
{
    //dtor
}

void Character::affiche(sf::RenderWindow& app, sf::Vector2f& pos)
{
    pos.y -= 32; //TODO: Améliorer, ça: pourquoi ajouter 32? (hauteur du perso)

    m_sprite.SetPosition(pos);
    app.Draw(m_sprite);

    //TODO: mettre ça autrepart
    move();
}

bool Character::gotoPos(sf::Vector2i pos)
{
    m_movementStack = m_map.pathFind(getPosition(), pos);
}

void Character::move()
{
    if (!m_movementStack.empty())
    {
        m_pos = *(m_movementStack.end() - 1);
        m_movementStack.pop_back();
    }
}
