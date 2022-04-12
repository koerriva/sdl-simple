#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update(){
    for (auto const o : m_GameObjects)
    {
        o->update();
    }
}

void PlayState::render(){
    for (auto const o : m_GameObjects)
    {
        o->draw();
    }
}

bool PlayState::onEnter(){
    std::cout << "entring PlayState" << std::endl;

    auto textureManager = TextureManager::Instance();
    auto renderer = Game::Instance()->getRenderer();

    TextureManager::Instance()->load("data/Knight_Idle.png","knight-idle",renderer);
    TextureManager::Instance()->load("data/Knight_Run.png","knight-run",renderer);

    GameObject* player = new Player(new LoaderParams(300,300,120,80,"knight-run"));

    m_GameObjects.push_back(player);

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
    textureManager->clearFromTextureMap("knight-run");
    textureManager->clearFromTextureMap("knight-idle");

    return true;
}