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
            maCase->SetPosition(i*96, j*64);
            maCase->SetSubRect(sf::IntRect(3*96, 0, 4*96, 64));

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

sf::Vector2<int> Map::toIso(int x, int y)
{
    //x += w/2 - 0.5;
    //y -= h/2 - 0.5;

	y *= 48;
	x *= 48;

	float a = std::atan2(y, x);
	int d = std::sqrt(x*x + y*y);		// en polaire

	a += M_PI / 4;						// rajoute 45°

	x = std::cos(a) * d;				// retour en cartésien
	y = std::sin(a) * d;

	y *= 0.45;
	x *= 34.8 / 48.0;					// "aplatit", et ajuste

	x += 48 * (m_w/2 - 0.5); // ajustement
	//y -= 210; // ajustement
}

sf::Vector2<int> Map::fromIso(int x, int y)
{
	x -= 48 * (m_w/2 - 0.5); // ajustement
	//y += 210; // ajustement

	y /= 0.45;
	x /= 34.8 / 48.0;

	float a = std::atan2(y, x);			// en polaire
	int d = std::sqrt(x*x + y*y);

	a -= M_PI / 4;						// enlève les 45°

	x = std::cos(a) * d;
	y = std::sin(a) * d;				// retour en cartésien

	float _y = (float)y / 48 + 0.5;
	float _x = (float)x / 48 - 0.5;

	y = (_y < 0)? _y-1 : _y;
	x = (_x < 0)? _x-1 : _x;
}
