#include <vector>
#include "Map.h"
#include <cmath>
#include "Character.h"
#include "JSON.h"
#include "StaticEntity.h"
//#include <sstream>

Map::Map(int w, int h) :
    m_w(w),
    m_h(h),
    m_map(NULL),
    m_character(NULL)
{
    /// Charge le tileset

    loadTileset("gfx/tileset.png");

    /// Remplit

    m_map = new Case**[m_w];

    for (int i = 0; i<m_w; i++)
    {
        m_map[i] = new Case*[m_h];
        for (int j = 0; j<m_h; j++)
        {
            Case*& maCase = m_map[i][j];

            maCase = new Case(*this, i, j);

            /// Tileset et zone à prendre (src_dst)

            maCase->setTex(&m_tileset);
            maCase->setGround(0, 0);

            /// Isométrie

            sf::Vector2f v(i, j);
            toIso(v);
            maCase->setPos(v.x, v.y);

            /// Affiche coordonnées avant/après iso.
            //std::cout << i   << ", " << j   << " => "
            //          << v.x << ", " << v.y << std::endl;
        }
    }

    /// Curseur

    m_cursImg.loadFromFile("gfx/curs.png");
    m_curs.setTexture(m_cursImg);

}

Map::Map(std::string nom) : m_map(NULL), m_character(NULL)
{
    m_w = 0;
    m_h = 0;

    JSON objetMap("map/"+nom+".json");

    assert(objetMap.IsObject());
	assert(objetMap.HasMember("map"));
	assert(objetMap.HasMember("tiles"));
	assert(objetMap["tiles"].IsString());
	assert(objetMap.HasMember("cases"));

	const js::Value& cases = objetMap["cases"];
	assert(cases.IsObject());

	const js::Value& carte = objetMap["map"];
	assert(carte.IsArray());

    /// Assignation des dimensions m_w et m_h à partir du tableau de "map"

	for (js::SizeType i = 0; i < carte.Size(); i++)
    {
        assert(carte[i].IsString());

        /// m_w prend la valeur max des largeurs de carte

        m_w = ((m_w<(int)carte[i].GetStringLength()) ? (int)carte[i].GetStringLength() : m_w);
        m_h ++;
    }

    JSON objetTiles(std::string("map/")+objetMap["tiles"].GetString());
    assert(objetTiles.IsObject());
    assert(objetTiles.HasMember("tileset"));
    assert(objetTiles.HasMember("terrains"));
    assert(objetTiles.HasMember("objects"));

    /// Charge le tileset à partir du fichier renseigné dans celui de map

    loadTileset(std::string("gfx/")+objetTiles["tileset"].GetString());

    const js::Value& sol = objetTiles["terrains"];
	assert(sol.IsObject());

	const js::Value& objets = objetTiles["objects"];
	assert(objets.IsObject());

    /// Remplit

    m_map = new Case**[m_w];

    for (int i = 0; i<m_w; i++)
    {
        m_map[i] = new Case*[m_h];

        for (int j = 0; j<m_h; j++)
        {
            Case*& maCase = m_map[i][j];

            maCase = new Case(*this, i, j);

            /// Tileset
            maCase->setTex(&m_tileset);

            /// On attribue chaque ligne de la map à une chaine de charactères
            std::string mapLine = carte[j].GetString();

            /// Puis la colonne i détermine le charactère lu

            // on "transforme" le caractère en chaîne (le caractère en question
            // suivi du caractère nul)
            char index[] = {mapLine.at(i), '\0'};

            /// Qui sert ensuite de clef à la lecture de l'objet de "cases"
            /// correspondant
            const js::Value& caseLine = cases[index];

            /**
              * Objet qui détermine le type de terrain appliqué à la case
              * en le faisant correspondre à l'attribut "name" de "terrains"
              * du fichier de tiles
              */

            int coutSol = 0, coutObj = 0;

            /// Ici test prend tour à tour les valeurs de l'attribut "name" pour
            /// le test
            /*
            for (js::SizeType n = 0; n < sol.Size(); n++)
            {
                test = sol[n]["name"].GetString();
                if(caseLine["terr"].GetString() == test)
                {
                    /// On lira le tileset selon xpos et ypos

                    maCase->setGround(sol[n]["xpos"].GetInt(),
                                      sol[n]["ypos"].GetInt());

                    coutSol = sol[n]["cost"].GetInt();
                }
            }*/
            const js::Value& caseTerr = objetTiles["terrains"][caseLine["terr"].GetString()];
            assert(caseTerr.IsObject());
            /// On lira le tileset selon xpos et ypos

            maCase->setGround(caseTerr["xpos"].GetInt(),
                              caseTerr["ypos"].GetInt());

            coutSol = caseTerr["cost"].GetInt();



            const js::Value& caseObjArray = caseLine["objs"];
            coutObj = 0;

            for (js::SizeType k = 0; k < caseObjArray.Size(); k++)
            {
                js::Value& caseObj = objetTiles["objects"][caseObjArray[k].GetString()];
                assert(caseObj.IsObject());

                if (caseObj.HasMember("entity") && caseObj["entity"].GetBool())
                {
                    StaticEntity* obj = new StaticEntity(*this);

                    obj->setTileset(m_tileset);
                    obj->setCase(*maCase);
                    obj->setPositionOnTileset(caseObj["xpos"].GetInt(),
                                              caseObj["ypos"].GetInt(),
                                              caseObj["width"].GetInt(),
                                              caseObj["height"].GetInt(),
                                              caseObj["centerx"].GetInt(),
                                              caseObj["centery"].GetInt());

                    coutObj += caseObj["cost"].GetInt();
                }
                else
                {
                    if (caseObj.HasMember("width") && caseObj.HasMember("height"))
                    {
                        maCase->setObject(caseObj["xpos"].GetInt(),
                                          caseObj["ypos"].GetInt(),
                                          caseObj["width"].GetInt(),
                                          caseObj["height"].GetInt());
                    }
                    else
                    {
                        maCase->setObject(caseObj["xpos"].GetInt(),
                                          caseObj["ypos"].GetInt());
                    }

                    // ajuste la position de l'image par apport à celle de la case
                    if (caseObj.HasMember("centerx") && caseObj.HasMember("centery"))
                    {
                        maCase->setRelativeObjectImagePos(-caseObj["centerx"].GetInt(),
                                                          -caseObj["centery"].GetInt());
                    }

                    coutObj += caseObj["cost"].GetInt();
                }
            }


            maCase->setCost(coutSol + coutObj);

            /// Isométrie

            sf::Vector2f v(i, j);
            toIso(v);
            maCase->setPos(v.x, v.y);
        }
    }

    /// Curseur

    m_cursImg.loadFromFile("gfx/curs.png");
    m_curs.setTexture(m_cursImg);
}

Map::~Map()
{
    /// Vide la map

    for (int i = 0; i<m_w; i++)
    {
        for (int j = 0; j<m_h; j++)
        {
            delete m_map[i][j];
        }

        delete[] m_map[i];
    }

    delete m_map;
}

void Map::loadTileset(std::string path)
{
    if (!m_tileset.loadFromFile(path))
    {
        ///TODO: Utiliser une exception?

        std::cerr << "Le chargement du tileset a échoué" << std::endl;
    }
}

void Map::affiche(sf::RenderWindow& app)
{
    /// Affiche les cases

    for (int i = 0; i<m_w; i++)
    {
        for (int j = 0; j<m_h; j++)
        {
            app.draw(getCaseAt(i, j)->getTerrain());

            if(getCaseAt(i, j)->hasObject())
            {
                app.draw(getCaseAt(i, j)->getObjet());
            }
        }
    }

    /// Affiche le curseur

    app.draw(m_curs);

    /// Affiche les entités

    reorderEntities();

    for (std::list<Entity*>::iterator   it = m_entities.begin();
                                        it != m_entities.end();
                                      ++it)
    {
        /// Isométrie
        //sf::Vector2i pos1 = (*it)->getPosition();
        //sf::Vector2f pos = sf::Vector2f(pos1.x, pos1.y);
        //toIso(pos);

        /// Affichage
        (*it)->affiche(app);
    }

}

void Map::registerEntity(Entity& e)
{
    /// Ajoute à la liste d'entités

    m_entities.push_back(&e);
    m_entities.sort();
}

void Map::registerCharacter(Character& c)
{
    /// Ajoute à la liste d'entités

    m_character = &c;
}

void Map::mouseDown(sf::Event evt)
{
    /// Clic gauche: déplacer le personnage jusqu'au curseur

    if (evt.mouseButton.button == sf::Mouse::Left)
    {
        if (!m_character)
            std::cerr << "merde..." << std::endl;
        m_character->gotoPos(m_cursPos, false);
    }
}

void Map::mouseMove(sf::Event evt)
{
    setCursorPos(sf::Vector2f(evt.mouseMove.x, evt.mouseMove.y));
}

void Map::setCursorPos(sf::Vector2f v)
{
    /// Coords normales

    fromIso(v);
    v.x--; /// ajustement (??)

    m_cursPos.x = round(v.x);
    m_cursPos.y = round(v.y);

    /// Reconvertit en iso

    sf::Vector2f v2(m_cursPos.x, m_cursPos.y);
    toIso(v2);
    m_curs.setPosition(v2);
}

sf::Vector2f Map::getCursorPos()
{
    return m_curs.getPosition();
}

std::vector<sf::Vector2i> Map::findPath(sf::Vector2i sourcePos,
                                        sf::Vector2i targetPos)
{
    /**
      * On s'arrête si la liste fermée est vide (pas de chemin)
      * ou si l'arrivée est dans la liste fermée
      * TODO: Surveiller la mémoire!!
      *
      * std::cout << "pathfinding start" << std::endl;
      *
      * Amélioration: utiliser une liste triée pour avoir le plus petit F en 1er?
      * ou garder trace du plus petit F pour ne pas avoir à boucler
      */

    Node target(NULL, targetPos.x, targetPos.y, getCaseAt(targetPos));
    Node source(NULL, sourcePos.x, sourcePos.y, getCaseAt(targetPos));

    source.target = &target;
    target.target = &target;

    /*
     * std::cout << "target: ("
     * << target.x << ", " << target.y
     * << ')' << std::endl;
     */

    std::vector<Node*> open, closed;
    //Node* openLowest = NULL;

    open.push_back(&source);
    //openLowest = &source;
    source.g = 0;

    bool loop = true;
    while (!open.empty() && loop)
    {
        std::vector<Node*>::iterator it;
        std::vector<Node*>::iterator currentIt;
        Node* current = NULL;

        /// On prend l'élément qui a le plus petit F

        it = open.begin();
        currentIt = it;
        current = *currentIt;
        int lowerF = current->getF();

        for (++it ; it != open.end(); ++it)
        {
            if ((*it)->getF() < lowerF)
            {
                currentIt = it;
                current = *currentIt;
                lowerF = current->getF();
            }
        }


        /// déplace 'current' dans la liste fermée

        open.erase(currentIt);
        closed.push_back(current);

        /// Recherche des voisins

        std::vector<Node*> neighbors;
        for (int i=-1; i<=1; i++)
        {
            for (int j=-1; j<=1; j++)
            {
                /**
                  * Ajoute le noeud aux voisins si ce n'est pas le noeud courant
                  * et si le noeud est traversable
                  * et s'il n'est pas dans la liste fermée
                  */

                bool notInClosed = true;
                Case* currentCase = getCaseAt(current->x+i, current->y+j);

                for (it = closed.begin(); it!=closed.end() && notInClosed; ++it)
                {
                    if ((*it)->x == current->x+i &&
                        (*it)->y == current->y+j)
                    notInClosed = false;
                }

                std::cout << "loooolll" << std::endl;
                if ((i || j) && notInClosed
                    && isWalkable(current->x+i, current->y+j)
                    && ( (!i || !j) || (isWalkable(current->x, current->y+j)
                                        && isWalkable(current->x+i, current->y))
                       )
                   )
                {
                    Node* c = new Node(current, current->x+i, current->y+j, currentCase);
                    std::cout << ">> " << currentCase->getCost() << std::endl;
                    c->g = current->g + ((i && j)? 14:10)*currentCase->getCost();
                    //c->h = abs(c->x - target.x) + abs(c->y - target.y);

                    neighbors.push_back(c);
                }
            }
        }

        /// Boucle sur les voisins...

        for (it = neighbors.begin(); it != neighbors.end(); ++it)
        {
            Node* neigh = *it;
            bool found = false;

            std::vector<Node*>::iterator open_n;
            for (open_n = open.begin(); open_n != open.end(); ++open_n)
            {
                if ((*open_n)->x == neigh->x &&
                    (*open_n)->y == neigh->y)
                {
                    found = true;
                    break;
                }
            }

            /// Si le voisin est dans la liste ouverte, plus court chemin?
            /// sinon, on l'ajoute simplement

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

        }

        if (current->x == target.x && current->y == target.y)
        {
            target = *current;
            //std::cout << "LOOL\n";
            break;
        }
    }

    std::cout << "loll" << std::endl;
    /// On remonte par parents depuis target

    std::vector<sf::Vector2i> res;
    Node* node = &target;
    bool foundPath;
    while (node != NULL)
    {
        res.push_back(sf::Vector2i(node->x, node->y));

        /// Si le noeud parent est nul, on a soit target soit source.
        /// si c'est source, le chemin a été trouvé

        if (node->parent == NULL)
            foundPath = (node == &source);

        node = node->parent;
    }


    /// Si un chemin a été trouvé, le renvoie. Sinon renvoie une liste vide.

    return foundPath? res : std::vector<sf::Vector2i>();
}

bool Map::withinBounds(int x, int y)
{
    return x >= 0 && y >= 0 && x < m_w && y < m_h;
}

Case* Map::getCaseAt(int x, int y)
{
    if (withinBounds(x, y))
        return m_map[x][y];

    return NULL;
}

Case* Map::getCaseAt(sf::Vector2i& v)
{
    if (withinBounds(v.x, v.y))
        return m_map[v.x][v.y];
    else
        std::cerr << "case hors limites" << std::endl;

    return NULL;
}

float Map::getElapsedTime()
{
    return m_clock.getElapsedTime().asSeconds();
}

void Map::loadTest()
{
    std::cout << "JSON:" << std::endl;

    JSON j("map/default-map.json");

    assert(j.IsObject());
	assert(j.HasMember("map"));
	assert(j.HasMember("tiles"));
	assert(j["tiles"].IsString());
	printf("tiles path = %s\n", j["tiles"].GetString());
    assert(j.HasMember("cases"));
    const js::Value& a = j["cases"];
    assert(a.IsArray());

    for (js::SizeType i = 0; i < a.Size(); i++)
    {
        assert(a[i].IsObject());

        printf(" - char: %c; terr: %s;\n", a[i]["char"].GetString()[0], a[i]["terr"].GetString());
    }

    /*
     * const js::Value& b = j["map"];
     *
     * delete m_map;
     * m_map = new Case**[b.Size()];
     *
     * for (js::SizeType i = 0; i < b.Size(); i++)
     * {
     *      m_map[i] = new Case*[b[i].Size()];
     *      assert(b[i].IsString());
     *      for(js::SizeType j = 0; j < b[i].Size(); j++)
     *      {
     *          Case*& maCase = m_map[i][j];
     *          maCase = new Case(*this, i, j);
     *          maCase->setTexture(m_tileset);
     *          maCase->setPositionOnTileset(0, 0);
     *
     *          sf::Vector2f v(i, j);
     *          toIso(v);
     *          maCase->setPosition(v.x, v.y);
     *      }
     *  }
     */
}

bool Map::isWalkable(int x, int y)
{
    return withinBounds(x, y) && getCaseAt(x, y)->isWalkable();
}

void Map::toIso(sf::Vector2f& v)
{
    float a = std::atan2(v.y, v.x);
    float d = std::sqrt(v.x*v.x + v.y*v.y);     /// en polaire

    a += M_PI_4;                                /// rajoute 45°

    v.x = std::cos(a) * d;                      /// retour en cartésien
    v.y = std::sin(a) * d;

    v.x *= M_SQRT2 * (Case::WIDTH/2);
    v.y *= M_SQRT2 * (Case::HEIGHT/2);

    /// Ajustement
    v.x += ( SCREEN_W - Case::WIDTH )/2;
    v.y += ( SCREEN_H - Case::HEIGHT * std::sqrt(m_w*m_h) )/2;
}

void Map::fromIso(sf::Vector2<float>& v)
{
    /// Ajustement
    v.x -= ( SCREEN_W - Case::WIDTH )/2;
    v.y -= ( SCREEN_H - Case::HEIGHT * std::sqrt(m_w*m_h) )/2;

    v.x /= M_SQRT2 * (Case::WIDTH/2);
    v.y /= M_SQRT2 * (Case::HEIGHT/2);

    float a = std::atan2(v.y, v.x);
    float d = std::sqrt(v.x*v.x + v.y*v.y);     /// en polaire

    a -= M_PI_4;                                /// enlève 45°

    v.x = std::cos(a) * d;                      /// retour en cartésien
    v.y = std::sin(a) * d;
}

bool compareEntities(Entity* first, Entity* second)
{
    return (*first) < (*second);
}

void Map::reorderEntities()
{
    m_entities.sort(compareEntities);
}
