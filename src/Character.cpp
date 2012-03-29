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

    m_sprite.SetPosition(spritePos(m_pos));
}

Character::~Character()
{
    //dtor
}

void Character::affiche(sf::RenderWindow& app)
{
    //pos.y -= 32; //TODO: Améliorer ça: pourquoi ajouter 32? (hauteur du perso)

    //m_sprite.SetPosition(pos);
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
        int speed = 4;
        sf::Vector2i nextPos = *(m_movementStack.end() - 1);
        sf::Vector2f curIsoPos, nextIsoPos, v;

        curIsoPos = m_sprite.GetPosition();

        nextIsoPos = spritePos(nextPos);

        v.x = nextIsoPos.x - curIsoPos.x;
        v.y = nextIsoPos.y - curIsoPos.y;

        float a = std::atan2(v.y, v.x);
        float d = std::sqrt(v.x*v.x + v.y*v.y);        // en polaire

        v.x = std::cos(a) * speed;                // retour en cartésien
        v.y = std::sin(a) * speed;

        m_sprite.SetPosition(curIsoPos.x + v.x, curIsoPos.y + v.y);

        if (d < speed)
        {
            m_pos = nextPos;
            m_sprite.SetPosition(nextIsoPos);
            m_movementStack.pop_back();
        }
    }
}

sf::Vector2f Character::spritePos(sf::Vector2i v)
{
    sf::Vector2f v2(v.x, v.y);
    m_map.toIso(v2);
    v2.y -= 32;
    return v2;
}
