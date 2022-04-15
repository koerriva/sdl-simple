#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "Base64.h"
#include "Layer.h"
#include "TileLayer.h"
#include <iostream>

Level* LevelParser::parseLevel(const char* levelFile){
    //load xml
    XMLDocument doc;
    auto err = doc.LoadFile(levelFile);
    if(err != XML_SUCCESS){
        std::cerr << "load level error!\n";
        return nullptr;
    }

    //create level
    Level* level = new Level();

    auto mapRoot = doc.RootElement();
    m_tileSize = mapRoot->IntAttribute("tilewidth");
    m_width = mapRoot->IntAttribute("width");
    m_height = mapRoot->IntAttribute("height");

    //parse tileset
    for (XMLElement* e = mapRoot->FirstChildElement("tileset");e; e=e->NextSiblingElement("tileset"))
    {
        parseTilesets(e,level->getTilesets());
    }

    //parse layer
    for (XMLElement* e = mapRoot->FirstChildElement("layer");e; e=e->NextSiblingElement("layer"))
    {
        parseTileLayer(e,level->getLayers(),level->getTilesets());
    }
    
    return level;
}


void LevelParser::parseTilesets(XMLElement* root,std::vector<Tileset>* tilesets){
    auto tm = TextureManager::Instance();

    auto imgNode = root->FirstChildElement("image");
    tm->load(imgNode->Attribute("source"),root->Attribute("name"),Game::Instance()->getRenderer());

    Tileset tileset;
    tileset.width = imgNode->IntAttribute("width");
    tileset.height = imgNode->IntAttribute("height");
    tileset.firstGridID = root->IntAttribute("firstgid");
    tileset.tileWidth = root->IntAttribute("tilewidth");
    tileset.tileHeight = root->IntAttribute("tileheight");
    tileset.spacing = root->IntAttribute("spacing");
    tileset.margin = root->IntAttribute("margin");
    tileset.name = root->Attribute("name");

    tileset.numColumns = root->IntAttribute("columns");
    tileset.count = root->IntAttribute("tilecount");
    tileset.numRows = tileset.count/tileset.numColumns;

    tilesets->push_back(tileset);
}

const std::string WHITESPACE = " \n\r\t\f\v";
 
std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

void LevelParser::parseTileLayer(XMLElement* root,std::vector<Layer*>* layers,const std::vector<Tileset>* tilesets){
    int width = root->IntAttribute("width");
    int height = root->IntAttribute("height");

    TileLayer* tileLayer = new TileLayer(m_tileSize,*tilesets);

    //tile data
    Base64 base64;
    std::vector<std::vector<int>> data;

    std::vector<int> decodedIDs;
    auto dataNode = root->FirstChildElement("data");
    std::string encodeData = dataNode->FirstChild()->Value();
    encodeData = trim(encodeData);

    std::cout << "size : " << encodeData.size() << "," << encodeData << std::endl;
    
    size_t outlen = 0;
    decodedIDs = base64.decode(encodeData,&outlen);

    std::vector<int> layerRow(m_width);

    for (size_t i = 0; i < m_height; i++)
    {
        data.push_back(layerRow);
    }

    for (size_t row = 0; row < m_height; row++)
    {
        for (size_t col = 0; col < m_width; col++)
        {
            data[row][col] = decodedIDs[row* m_width + col];
        }
    }

    tileLayer->setTileIDs(data);

    layers->push_back(tileLayer);
}