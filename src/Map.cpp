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

            maCase = new Case(*this);

            // tileset et zone à prendre (src_dst)
            maCase->SetImage(m_tileset);
            maCase->SetSubRect(sf::IntRect(0*Case::WIDTH,
                                           0,
                                           1*Case::WIDTH,
                                           Case::HEIGHT));

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
	float d = std::sqrt(v.x*v.x + v.y*v.y);		// en polaire

	a -= M_PI / 4;						        // enlève 45°

	v.x = std::cos(a) * d;				// retour en cartésien
	v.y = std::sin(a) * d;
}
