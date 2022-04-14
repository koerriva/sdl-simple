#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include "GameObject.h"

class BaseCreator {
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {};
};

class GameObjectFactory
{
private:
    std::unordered_map<std::string,BaseCreator*> m_creators;

    static GameObjectFactory* s_Instance;
public:

    static GameObjectFactory* Instance(){
        if(s_Instance==nullptr){
            s_Instance = new GameObjectFactory();
        }

        return s_Instance;
    }

    bool registerType(std::string typeID, BaseCreator* creator);
    GameObject* create(std::string typeID);
};
