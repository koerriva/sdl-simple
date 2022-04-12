#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update(){

    auto ih = InputHandler::Instance();
    if(ih->isKeyDown(SDL_SCANCODE_ESCAPE)){
        Game::Instance()->getStateMachine()->pushState(new PauseState());
    }

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
    TextureManager::Instance()->load("data/Knight_Hit.png","knight-hit",renderer);
    TextureManager::Instance()->load("data/Knight_DeathNoMovement.png","knight-death",renderer);
    TextureManager::Instance()->load("data/Knight_AttackNoMovement.png","knight-attack",renderer);

    TextureManager::Instance()->load("data/Knight2_Idle.png","enemy-idle",renderer);
    TextureManager::Instance()->load("data/Knight2_Run.png","enemy-run",renderer);
    TextureManager::Instance()->load("data/Knight2_Hit.png","enemy-hit",renderer);
    TextureManager::Instance()->load("data/Knight2_DeathNoMovement.png","enemy-death",renderer);
    TextureManager::Instance()->load("data/Knight2_AttackNoMovement.png","enemy-attack",renderer);

    GameObject* player = new Player(new LoaderParams(300,300,120,80,"knight-run"));
    GameObject* enemy = new Enemy(new LoaderParams(400,300,120,80,"enemy-attack"));

    m_GameObjects.push_back(player);
    m_GameObjects.push_back(enemy);

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
    textureManager->clearFromTextureMap("knight-hit");
    textureManager->clearFromTextureMap("knight-death");
    textureManager->clearFromTextureMap("knight-attack");

    textureManager->clearFromTextureMap("enemy-run");
    textureManager->clearFromTextureMap("enemy-idle");
    textureManager->clearFromTextureMap("enemy-hit");
    textureManager->clearFromTextureMap("enemy-death");
    textureManager->clearFromTextureMap("enemy-attack");

    return true;
}