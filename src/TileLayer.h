#pragma once

#include "Layer.h"
#include "Level.h"
#include <glm/glm.hpp>

using namespace glm;

class TileLayer : public Layer
{
private:
    int m_numColumns;
    int m_numRows;
    int m_tileSize;

    ivec2 m_position;
    ivec2 m_velocity;

    std::vector<Tileset> m_tilesets;
    std::vector<std::vector<int>> m_tileIDs;
public:
    TileLayer(int tileSize,const std::vector<Tileset>& tilesets);
    
    virtual void update();
    virtual void render();

    void setTileIDs(const std::vector<std::vector<int>> tileIDs){
        m_tileIDs = tileIDs;
    }

    void setTilesize(int tileSize) {
        m_tileSize = tileSize;
    }

    Tileset getTilesetByID(int tileID);
};