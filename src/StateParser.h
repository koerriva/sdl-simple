#pragma once

#include <vector>
#include <iostream>
#include "tinyxml2.h"

using namespace tinyxml2;

class GameObject;

class StateParser
{
public:
    StateParser();
    ~StateParser(){};

    bool parseState(const char* stateFile,std::string stateID
        ,std::vector<GameObject*>* gameObjects
        ,std::vector<std::string>* textureIDs);

private:
    void parseObjects(XMLElement* root,std::vector<GameObject*>* objects);
    void parseTextures(XMLElement* root,std::vector<std::string>* textureIDs);
};
