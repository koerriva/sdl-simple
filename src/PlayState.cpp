#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "LevelParser.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update(){

    auto ih = InputHandler::Instance();
    if(ih->isKeyDown(SDL_SCANCODE_ESCAPE)){
        Game::Instance()->getStateMachine()->pushState(new PauseState());
    }

    m_currentLevel->update();
    for (auto const o : m_GameObjects)
    {
        o->update();
    }

    GameObject* player = m_GameObjects[0];
    GameObject* enemy = m_GameObjects[1];

    bool hit = checkCollision(dynamic_cast<SDLGameObject*>(player),dynamic_cast<SDLGameObject*>(enemy));
    if(hit){
        Game::Instance()->getStateMachine()->pushState(new GameOverState());
    }
}

void PlayState::render(){
    m_currentLevel->render();
    for (auto const o : m_GameObjects)
    {
        o->draw();
    }
}

bool PlayState::onEnter(){
    std::cout << "entring PlayState" << std::endl;

    StateParser stateParser;
    stateParser.parseState("game.xml",s_playID,&m_GameObjects,&m_textureIDs);

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

bool PlayState::checkCollision(SDLGameObject* p1,SDLGameObject* p2){
    SDL_Rect* p1Rect =  p1->getCollisionRect();
    SDL_Rect* p2Rect =  p2->getCollisionRect();
    SDL_Rect result;

    return SDL_IntersectRect(p1Rect,p2Rect,&result);
}