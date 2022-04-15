#pragma once

#include <string>
#include <vector>

#include "Layer.h"

struct Tileset{
    int firstGridID=0;
    int tileWidth=0;
    int tileHeight=0;
    int spacing=0;
    int margin=0;
    int width=0;
    int height=0;
    int count=0;
    int numColumns=0;
    int numRows=0;
    std::string name;
};

class Level
{
private:
    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;

    friend class LevelParser;
    Level(){};
    
public:
    ~Level(){};

    void update();
    void render();

    std::vector<Tileset>* getTilesets() { return &m_tilesets;}
    std::vector<Layer*>* getLayers() {return &m_layers;}
};
