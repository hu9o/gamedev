#include "Tileset.h"

#include <string>
#include "JSON.h"

Tileset::Tileset(std::string path) :
    j(path)
{
    std::cout << "JSON2:" << std::endl;

    std::string tilesetPath = "gfx/";
    tilesetPath += j["tileset"].GetString();

	printf("tileset path = %s\n", tilesetPath.c_str());

	img.loadFromFile(tilesetPath);
}

Tileset::~Tileset()
{
    //dtor
}

sf::Image Tileset::getImage()
{
    return img;
}

// DEVRAIT RETOURNER UNE CASE???
sf::IntRect Tileset::getTerrain(std::string name)
{
    assert(j.HasMember("terrains"));

    const js::Value& terrains = j["terrains"];

    assert(terrains.IsObject());
/*
    if (terrains.HasMember(name))
    {
        //getCoordsOnTileset(terrains[name]["xpos"], terrains[name]["ypos"]);
    }
    else
    {
        std::cerr << "le terrain \"" << name << "\" est introuvable." << std::endl;
    }*/
}

