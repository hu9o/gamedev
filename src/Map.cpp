#include "Map.h"

Map::Map(int w, int h) :
    m_map(NULL),
    m_w(w),
    m_h(h)
{

    // charge le tileset
    loadTileset("gfx/tileset.png");

    // remplit

    m_map = new Case**[m_w];

    if (!m_tileset.GetWidth() == 0 && m_tileset.GetHeight() == 0)
        exit(1);

    for (int i = 0; i<m_w; i++)
    {
        m_map[i] = new Case*[m_h];

        for (int j = 0; j<m_h; j++)
        {
            Case*& maCase = m_map[i][j];

            maCase = new Case();

            maCase->SetImage(m_tileset);
            maCase->SetSubRect(sf::IntRect(0*96, 0, 1*96, 64));

            // isométrie!
            sf::Vector2<float> v(i, j);
            toIso(v);
            maCase->SetPosition(v.x, v.y);

            std::cout << i << ", " << j << std::endl;
        }
    }

    ////

}


Map::~Map()
{
    // vide

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
    m_tileset.LoadFromFile(path);
    m_tileset.SetSmooth(false);
}

void Map::affiche(sf::RenderWindow& app)
{
    for (int i = 0; i<m_w; i++)
    {
        for (int j = 0; j<m_h; j++)
        {
            app.Draw(*m_map[i][j]);
        }
    }
}

void Map::toIso(sf::Vector2<float>& v)
{
	float a = std::atan2(v.y, v.x);
	float d = std::sqrt(v.x*v.x + v.y*v.y);		// en polaire

	a += M_PI / 4;						        // rajoute 45°

	v.x = std::cos(a) * d;				// retour en cartésien
	v.y = std::sin(a) * d;

	v.x *= 1.414 * 48;
	v.y *= 1.414 * 32;

	v.x += 320; // ajustement
	v.y += 160; // ajustement
}

void Map::fromIso(sf::Vector2<float>& v)
{
	v.x -= 320; // ajustement
	v.y -= 160; // ajustement

	v.x /= 1.414 * 48;
	v.y /= 1.414 * 32;

	float a = std::atan2(v.y, v.x);
	float d = std::sqrt(v.x*v.x + v.y*v.y);		// en polaire

	a -= M_PI / 4;						        // enlève 45°

	v.x = std::cos(a) * d;				// retour en cartésien
	v.y = std::sin(a) * d;
}
