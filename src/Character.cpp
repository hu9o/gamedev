#include "Character.h"

Character::Character(Map& map) : Entity(map)
{
    // charge image
    if (!m_image.LoadFromFile("gfx/charset.png"))
    {
        //TODO: Utiliser une exception?
        std::cerr << "Le chargement du tileset a échoué" << std::endl;
    }
    m_image.SetSmooth(false);
    m_sprite.SetImage(m_image);
    m_map.registerCharacter(*this);

    m_sprite.SetPosition(spritePos(m_pos));
    m_dir = 4;
    m_moving = false;
}

Character::~Character()
{
    //dtor
}

void Character::affiche(sf::RenderWindow& app)
{
    int imgNb = m_moving? (int)(m_map.getElapsedTime() * 6) % 4 : 0;

    m_sprite.SetSubRect(sf::IntRect( imgNb*32,      m_dir*48,
                                     imgNb*32 + 32, m_dir*48 + 48 ));

    //m_sprite.SetPosition(pos);
    app.Draw(m_sprite);

    //TODO: mettre ça autrepart
    move();
}

bool Character::gotoPos(sf::Vector2i pos)
{
    m_movementStack = m_map.pathFind(getPosition(), pos);

    return !m_movementStack.empty();
}

void Character::move()
{
    m_moving = !m_movementStack.empty();

    if (m_moving)
    {
        int speed = 1;
        sf::Vector2i nextPos = *(m_movementStack.end() - 1);
        sf::Vector2f curIsoPos, nextIsoPos, v;

        curIsoPos = m_sprite.GetPosition();

        nextIsoPos = spritePos(nextPos);

        v.x = nextIsoPos.x - curIsoPos.x;
        v.y = nextIsoPos.y - curIsoPos.y;

        float a = std::atan2(v.y, v.x);
        float d = std::sqrt(v.x*v.x + v.y*v.y);        // en polaire

        if (d > speed*2) m_dir = (int)((a + M_PI*2) / M_PI_4) % 8;

        //TODO: utiliser 'a' pour donne rla bonne valeur à m_dir (direction)

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
    v2.x += 8;
    v2.y -= 26;
    return v2;
}
