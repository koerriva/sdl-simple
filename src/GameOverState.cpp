#include "GameOverState.h"

#include "Game.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "StateParser.h"

#include <iostream>

const std::string GameOverState::s_GameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain(){
    Game::Instance()->getStateMachine()->changeState(new MainMenuState());
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

    // auto textureManager = TextureManager::Instance();
    // auto renderer = Game::Instance()->getRenderer();

    // textureManager->load("data/Continue_Button.png","continue_text",renderer);
    // textureManager->load("data/Menu_Button.png","menu_button",renderer);
    // textureManager->load("data/Resume_Button.png","resume_button",renderer);

    // GameObject* continue_text = new AnimatedGraphic(new LoaderParams(340,20,600,200,"continue_text",2));
    // GameObject* menu_button = new MenuButton(new LoaderParams(340,240,600,200,"menu_button"),s_gameOverToMain);
    // GameObject* resatrt_button = new MenuButton(new LoaderParams(340,460,600,200,"resume_button"),s_restartPlay);

    // m_GameObjects.push_back(continue_text);
    // m_GameObjects.push_back(menu_button);
    // m_GameObjects.push_back(resatrt_button);
    StateParser stateParser;
    stateParser.parseState("game.xml",s_GameOverID,&m_GameObjects,&m_textureIDs);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);
    setCallbacks(m_callbacks);
    
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
    for (auto t : m_textureIDs)
    {
        textureManager->clearFromTextureMap(t);
    }
    
    return true;
}

void GameOverState::setCallbacks(const std::vector<callback>& callbacks){
    for (auto o : m_GameObjects){
        MenuButton* button = dynamic_cast<MenuButton*>(o);
        if(button){
            button->setCallback(callbacks[button->getCallbackID()]);
        }
    }
}