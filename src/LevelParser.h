#pragma once

#include "Level.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class LevelParser
{
private:
    void parseTilesets(XMLElement* root,std::vector<Tileset>* tilesets);
    void parseTileLayer(XMLElement* root,std::vector<Layer*>* layers,const std::vector<Tileset>* tilesets);

    int m_tileSize;
    int m_width;
    int m_height;
    
public:
    LevelParser(){};
    ~LevelParser(){};

    Level* parseLevel(const char* levelFile);
};