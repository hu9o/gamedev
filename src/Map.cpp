#include "Map.h"
#include <cmath>
#include "Character.h"

Map::Map(int w, int h) :
    m_map(NULL),
    m_character(NULL),
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
            sf::Vector2f v(i, j);
            toIso(v);
            maCase->SetPosition(v.x, v.y);

            // affiche coordonnées avant/après iso.
            std::cout << i   << ", " << j   << " => "
                      << v.x << ", " << v.y << std::endl;
        }
    }

    ////

    // curseur
    m_cursImg.LoadFromFile("gfx/curs.png");
    m_curs.SetImage(m_cursImg);

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

    // affiche le curseur
    app.Draw(m_curs);

    // affiche les entités
    std::vector<Entity*>::iterator it = m_entities.begin();
    while (it != m_entities.end())
    {
        // isométrie
        sf::Vector2i pos1 = (*it)->getPosition();
        sf::Vector2f pos = sf::Vector2f(pos1.x, pos1.y);
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

void Map::registerCharacter(Character& c)
{
    // ajoute à la liste d'entités
    m_entities.push_back(&c);
    m_character = &c;
}

void Map::mouseDown(sf::Event evt)
{
    if (evt.MouseButton.Button == sf::Mouse::Left)
    {

        std::cout << m_cursPos.x << ", " << m_cursPos.y << std::endl;
        if (!m_character)
            std::cerr << "merde..." << std::endl;
        m_character->gotoPos(m_cursPos);
    }
}

void Map::mouseMove(sf::Event evt)
{
    setCursorPos(sf::Vector2f(evt.MouseMove.X, evt.MouseMove.Y));
}

void Map::setCursorPos(sf::Vector2f v)
{
    // coords normales
    fromIso(v);
    v.x--; // ajustement (??)

    m_cursPos.x = round(v.x);
    m_cursPos.y = round(v.y);

    // reconvertit en iso
    sf::Vector2f v2(m_cursPos.x, m_cursPos.y);
    toIso(v2);
    m_curs.SetPosition(v2);
}

sf::Vector2f Map::getCursorPos()
{
    return m_curs.GetPosition();
}

std::vector<sf::Vector2i> Map::pathFind(sf::Vector2i sourcePos,
                                        sf::Vector2i targetPos)
{
    // on s'arrête si la liste fermée est vide (pas de chemin)
    //   ou si l'arrivée est dans la liste fermée
    //TODO: Surveiller la mémoire!!

    ////std::cout << "pathfinding start" <<std::endl;

    // amélioration: utiliser une liste triée pour avoir le plus petit F en 1er?
    //   ou garder trace du plus petit F pour ne pas avoir à boucler

    Node target(NULL, targetPos.x, targetPos.y);
    Node source(NULL, sourcePos.x, sourcePos.y);

    source.target = &target;
    target.target = &target;

        ////std::cout << "target: ("
        ////          << target.x << ", " << target.y
        ////          << ')' << std::endl;

    std::vector<Node*> open, closed;
    //Node* openLowest = NULL;

    open.push_back(&source);
    //openLowest = &source;
    source.g = 0;

    bool loop = true;
    while (!open.empty() && loop)
    {
        ////std::cout << "loop" << std::endl;
        ////std::cout << "open:   " << open.size()   << std::endl;
        ////for (int i=0; i<open.size(); i++) std::cout << '(' << open[i]->x << ", " << open[i]->y << "), ";
        ////std::cout << std::endl;
        ////std::cout << "closed: " << closed.size() << std::endl;
        ////for (int i=0; i<closed.size(); i++) std::cout << '(' << closed[i]->x << ", " << closed[i]->y << "), ";
        ////std::cout << std::endl;

        std::vector<Node*>::iterator it;
        std::vector<Node*>::iterator currentIt;
        Node* current = NULL;


        // on prend l'élément qui a le plus petit F
        it = open.begin();
        currentIt = it;
        current = *currentIt;
        int lowerF = current->getF();
        ++it;

        while (it != open.end())
        {
            if ((*it)->getF() < lowerF)
            {
                currentIt = it;
                current = *currentIt;
                lowerF = current->getF();
            }
            ++it;
        }

        // affiche 'current':
        ////std::cout << "current: ("
        ////          << current->x << ", " << current->y
        ////          << ')' << std::endl;

        //sf::Sleep(1);

        // déplace 'current' dans la liste fermée
        open.erase(currentIt);
        closed.push_back(current);

        // recherche des voisins
        std::vector<Node*> neighbors;
        for (int i=-1; i<=1; i++)
        {
            for (int j=-1; j<=1; j++)
            {
                // ajoute le noeud aux voisins si ce n'est pas le noeud courant
                // et si le noeud est traversable
                if ((i || j)
                    && isWalkable(current->x+i, current->y+j)
                    && ( (!i || !j) || (isWalkable(current->x, current->y+j)
                                        && isWalkable(current->x+i, current->y))
                       )
                   )
                {
                    Node* c = new Node(current, current->x+i, current->y+j);
                    c->g = current->g + ((i && j)? 14:10);
                    //c->h = abs(c->x - target.x) + abs(c->y - target.y);

                    neighbors.push_back(c);
                }
            }
        }

        // boucle sur les voisins...
        it = neighbors.begin();
        while (it != neighbors.end())
        {
            Node* neigh = *it;
            bool found = false;

            std::vector<Node*>::iterator open_n = open.begin();
            while (open_n != open.end())
            {
                if ((*open_n)->x == neigh->x &&
                    (*open_n)->y == neigh->y)
                {
                    found = true;
                    break;
                }

                ++open_n;
            }

            // si le voisin est dans la liste ouverte, plus court chemin?
            // sinon, on l'ajoute simplement
            if (found)
            {
                if (neigh->g > (*open_n)->g)
                {
                    neigh->g = (*open_n)->g;
                    neigh->parent = current;
                    delete neigh;
                }

            }
            else
            {
                open.push_back(neigh);
            }

            ++it;
        }

        if (current->x == target.x && current->y == target.y)
        {
            target = *current;
            ////std::cout << "LOOL\n";
            break;
        }
        /* efface les cases créées
        while (!neighbors.empty())
        {
            delete *(neighbors.end()-1);
            neighbors.pop_back();
        }
        */
    }
    ////std::cout << "LOZEVOL";

    ////std::cout << "chemin: ";
    std::vector<sf::Vector2i> res;
    Node* node = &target;
    while (node != NULL)
    {
        ////std::cout <<'('<<node->x<<", "<<node->y<<"), ";
        res.push_back(sf::Vector2i(node->x, node->y));
        node = node->parent;
    }
    ////std::cout << std::endl;

    return res;
}

bool Map::isWalkable(int x, int y)
{
    return x >= 0 && y >= 0 && x < m_w && y < m_h && m_map[x][y]->isWalkable();
}

void Map::toIso(sf::Vector2f& v)
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
