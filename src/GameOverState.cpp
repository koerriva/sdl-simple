#include "GameOverState.h"

#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"

#include <iostream>

const std::string GameOverState::s_GameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain(){
    Game::Instance()->getStateMachine()->changeState(new MenuState());
}


void GameOverState::s_restartPlay(){
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::update(){
    for(auto const o : m_GameObjects){
        o->update();
    }
}

void GameOverState::render(){
    for(auto const o : m_GameObjects){
        o->draw();
    }
}

bool GameOverState::onEnter(){
    std::cout << "entering GameOverState\n";

    auto textureManager = TextureManager::Instance();
    auto renderer = Game::Instance()->getRenderer();

    textureManager->load("data/Continue_Button.png","continue_text",renderer);
    textureManager->load("data/Menu_Button.png","menu_button",renderer);
    textureManager->load("data/Resume_Button.png","resume_button",renderer);

    GameObject* continue_text = new AnimatedGraphic(new LoaderParams(340,20,600,200,"continue_text",2));
    GameObject* menu_button = new MenuButton(new LoaderParams(340,240,600,200,"menu_button"),s_gameOverToMain);
    GameObject* resatrt_button = new MenuButton(new LoaderParams(340,460,600,200,"resume_button"),s_restartPlay);

    m_GameObjects.push_back(continue_text);
    m_GameObjects.push_back(menu_button);
    m_GameObjects.push_back(resatrt_button);
    return true;
}

bool GameOverState::onExit(){
    std::cout << "exiting GameOverState\n";

    for (auto o : m_GameObjects)
    {
        o->clean();
    }

    m_GameObjects.clear();

    auto textureManager = TextureManager::Instance();
    textureManager->clearFromTextureMap("continue_text");
    
    return true;
}