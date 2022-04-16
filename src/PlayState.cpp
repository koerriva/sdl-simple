#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "ObjectLayer.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update(){

    auto ih = InputHandler::Instance();
    if(ih->isKeyDown(SDL_SCANCODE_ESCAPE)){
        Game::Instance()->getStateMachine()->pushState(new PauseState());
    }

    m_currentLevel->update();
    ObjectLayer* objectLayer = nullptr;
    std::vector<Layer*>* layers = m_currentLevel->getLayers();
    for (auto layer : *layers)
    {
        objectLayer = dynamic_cast<ObjectLayer*>(layer);
        if(objectLayer){
            break;
        }
    }

    if(objectLayer){
        Player* player = objectLayer->getPlayer();
        bool hit = false;
        for (auto enemy : objectLayer->getEnemies())
        {
            hit = checkCollision(player->getCollisionRect(),enemy->getCollisionRect());
            if(hit){
                break;
            }
        }

        if(hit){
            Game::Instance()->getStateMachine()->pushState(new GameOverState());
        }
    }
}

void PlayState::render(){
    m_currentLevel->render();
}

bool PlayState::onEnter(){
    std::cout << "entring PlayState" << std::endl;

    // StateParser stateParser;
    // stateParser.parseState("game.xml",s_playID,&m_GameObjects,&m_textureIDs);

    LevelParser levelParser;
    m_currentLevel = levelParser.parseLevel("terrain.tmx");

    return true;
}

bool PlayState::onExit(){
    std::cout << "exiting PlayState" << std::endl;
    for (auto const o : m_GameObjects)
    {
        o->clean();
    }
    m_GameObjects.clear();

    auto textureManager = TextureManager::Instance();

    for (auto const t : m_textureIDs){
        textureManager->clearFromTextureMap(t);
    }

    return true;
}

bool PlayState::checkCollision(SDL_Rect* r1,SDL_Rect* r2){
    SDL_Rect result;
    return SDL_IntersectRect(r1,r2,&result);
}