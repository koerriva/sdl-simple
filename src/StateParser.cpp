#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"

StateParser::StateParser(){
    
}

bool StateParser::parseState(const char* stateFile,std::string stateID,std::vector<GameObject*>* objects,std::vector<std::string>* textureIDs){
    XMLDocument doc;
    XMLError err = doc.LoadFile(stateFile);
    if(err!=XML_SUCCESS){
        std::cerr << "load xml error!\n";
        return false;
    }

    auto root = doc.RootElement();
    

    auto stateRoot = root->FirstChildElement(stateID.c_str());
    std::cout << "E : " << stateRoot->Name() << std::endl;

    //parse textures
    parseTextures(stateRoot->FirstChildElement("TEXTURES"),textureIDs);
    //parse objects
    parseObjects(stateRoot->FirstChildElement("OBJECTS"),objects);

    return true;
}

void StateParser::parseTextures(XMLElement* childRoot,std::vector<std::string> *textureIDs){
    std::cout << "E : " << childRoot->Name() << std::endl;

    for (XMLElement* e = childRoot->FirstChildElement("texture");e;e=e->NextSiblingElement("texture"))
    {
        std::cout << "E : " << e->Name() << std::endl;

        const char* filename = e->Attribute("filename");
        const char* id = e->Attribute("ID");

        textureIDs->push_back(id);

        TextureManager::Instance()->load(filename,id,Game::Instance()->getRenderer());
    }
}

void StateParser::parseObjects(XMLElement* childRoot,std::vector<GameObject*> *objects){
    std::cout << "E : " << childRoot->Name() << std::endl;

    XMLElement* e = childRoot->FirstChildElement("object");

    for (XMLElement* e = childRoot->FirstChildElement("object");e;e=e->NextSiblingElement("object"))
    {
        std::cout << "E : " << e->Name() << std::endl;

        const char* type = e->Attribute("type");
        int x = e->IntAttribute("x");
        int y = e->IntAttribute("y");
        int width = e->IntAttribute("width");
        int height = e->IntAttribute("height");
        int numFrames = e->IntAttribute("numFrames",1);
        int animtedSpeed = e->IntAttribute("animatedSpeed",10);
        const char* textureID = e->Attribute("textureID");
        int callbackID = e->IntAttribute("callbackID");

        GameObject* object = GameObjectFactory::Instance()->create(type);
        LoaderParams* params = new LoaderParams(x,y,width,height,textureID,numFrames,animtedSpeed,callbackID);
        object->load(params);

        objects->push_back(object);
    }
}