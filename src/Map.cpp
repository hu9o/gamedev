#include "Map.h"

Map::Map(int w, int h) :
    m_map(NULL),
    m_w(w),
    m_h(h)
{

//    // map de test, en attendant de la charger
//    struct
//    {
//        int x, y;
//    }
//    testmap[6][6] = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}},
//                    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
//                    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
//                    {{0, 0}, {0, 0}, {0, 4}, {0, 5}, {0, 6}, {0, 0}},
//                    {{0, 0}, {1, 0}, {1, 4}, {1, 5}, {1, 6}, {0, 0}},
//                    {{0, 0}, {0, 0}, {2, 4}, {2, 5}, {2, 6}, {0, 0}}};


    // charge le tileset
    loadTileset("gfx/tileset.png");

    // remplit

    m_map = new Case**[m_w];

    for (int i = 0; i<m_w; i++)
    {
        m_map[i] = new Case*[m_h];
        for (int j = 0; j<m_h; j++)
        {
            Case*& maCase = m_map[i][j];

            maCase = new Case(*this, i, j);

            // tileset et zone à prendre (src_dst)
            maCase->SetImage(m_tileset);
            maCase->setPositionOnTileset(std::rand()%2, 0);

            // isométrie!
            sf::Vector2<float> v(i, j);
            toIso(v);
            maCase->SetPosition(v.x, v.y);

            // affiche coordonnées avant/après iso.
            std::cout << i   << ", " << j   << " => "
                      << v.x << ", " << v.y << std::endl;
        }
    }

    ////

}


Map::~Map()
{
    // vide la map

    for (int i = 0; i<m_w; i++)
    {
        for (int j = 0; j<m_h; j++)
        {
            delete m_map[i][j];
        }

        delete[] m_map[i];
    }

    delete m_map;

    ////
}

void Map::loadTileset(std::string path)
{
    if (!m_tileset.LoadFromFile(path))
    {
        //TODO: Utiliser une exception?
        std::cerr << "Le chargement du tileset a échoué" << std::endl;
    }

    m_tileset.SetSmooth(false);
}


void Map::affiche(sf::RenderWindow& app)
{
    // affiche les cases
    for (int i = 0; i<m_w; i++)
    {
        for (int j = 0; j<m_h; j++)
        {
            app.Draw(*m_map[i][j]);
        }
    }

    // affiche les entités
    std::vector<Entity*>::iterator it = m_entities.begin();
    while (it != m_entities.end())
    {
        // isométrie
        sf::Vector2<int> pos1 = (*it)->getPosition();
        sf::Vector2<float> pos = sf::Vector2<float>(pos1.x, pos1.y);
        toIso(pos);

        // affichage
        (*it)->affiche(app, pos);
        it++;
    }

}

void Map::registerEntity(Entity& e)
{
    // ajoute à la liste d'entités
    m_entities.push_back(&e);
}

void Map::click(sf::Event evt)
{
    if (evt.MouseButton.Button == sf::Mouse::Left)
    {
        sf::Vector2<float> pos = sf::Vector2<float>(evt.MouseButton.X,
                                                    evt.MouseButton.Y);

        fromIso(pos);

        std::cout << pos.x << ", " << pos.y << std::endl;

    }
}

void Map::toIso(sf::Vector2<float>& v)
{
    float a = std::atan2(v.y, v.x);
    float d = std::sqrt(v.x*v.x + v.y*v.y);        // en polaire

    a += M_PI / 4;                                // rajoute 45°

    v.x = std::cos(a) * d;                // retour en cartésien
    v.y = std::sin(a) * d;

    v.x *= M_SQRT2 * (Case::WIDTH/2);
    v.y *= M_SQRT2 * (Case::HEIGHT/2);

    v.x += ( SCREEN_W - Case::WIDTH )/2;                        // ajustement
    v.y += ( SCREEN_H - Case::HEIGHT * std::sqrt(m_w*m_h) )/2; // ajustement
}

void Map::fromIso(sf::Vector2<float>& v)
{
    v.x -= ( SCREEN_W - Case::WIDTH )/2;                        // ajustement
    v.y -= ( SCREEN_H - Case::HEIGHT * std::sqrt(m_w*m_h) )/2; // ajustement

    v.x /= M_SQRT2 * (Case::WIDTH/2);
    v.y /= M_SQRT2 * (Case::HEIGHT/2);

    float a = std::atan2(v.y, v.x);
    float d = std::sqrt(v.x*v.x + v.y*v.y);        // en polaire

    a -= M_PI / 4;                                // enlève 45°

    v.x = std::cos(a) * d;                // retour en cartésien
    v.y = std::sin(a) * d;
}
