#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::s_Instance = nullptr;

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* creator){
    auto it = m_creators.find(typeID);
    if(it!=m_creators.end()){
        std::cerr << "Creator exist!\n";
        delete creator;
        return false;
    }

    m_creators[typeID] = creator;
    return true;
}

GameObject* GameObjectFactory::create(std::string typeID){
    auto it = m_creators.find(typeID);
    if(it==m_creators.end()){
        std::cerr << "Creator not found!\n";
        return nullptr;
    }
    BaseCreator* creator = m_creators[typeID];
    return creator->createGameObject();
}