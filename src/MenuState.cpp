#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "StateParser.h"

#include <iostream>

const std::string MainMenuState::s_MenuID = "MENU";

void MainMenuState::update(){
    for (auto const o : m_GameObjects)
    {
        o->update();
    }
}

void MainMenuState::render(){
    for (auto const o : m_GameObjects)
    {
        o->draw();
    }
}

bool MainMenuState::onEnter(){
    std::cout << "entring MenuState\n";

    // auto textureManager = TextureManager::Instance();
    // auto renderer = Game::Instance()->getRenderer();

    // textureManager->load("data/Play_Button.png","plan_button",renderer);
    // textureManager->load("data/Exit_Button.png","exit_button",renderer);

    // GameObject* plan_button = new MenuButton(new LoaderParams(340,150,600,200,"plan_button"),s_menuToPlay);
    // GameObject* exit_button = new MenuButton(new LoaderParams(340,370,600,200,"exit_button"),s_exitFromMenu);

    // m_GameObjects.push_back(plan_button);
    // m_GameObjects.push_back(exit_button);

    StateParser stateParser;
    stateParser.parseState("game.xml",s_MenuID,&m_GameObjects,&m_textureIDs);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);
    setCallbacks(m_callbacks);

    return true;
}

bool MainMenuState::onExit(){
    std::cout << "exiting MenuState" << std::endl;
    for (auto const o : m_GameObjects)
    {
        o->clean();
    }
    m_GameObjects.clear();

    auto textureManager = TextureManager::Instance();

    for (auto const t : m_textureIDs)
    {
        textureManager->clearFromTextureMap(t);
    }
    
    return true;
}

void MainMenuState::s_menuToPlay(){
    std::cout << "menu to play" << std::endl;
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu(){
    std::cout << "exit from menu" << std::endl;
    Game::Instance()->quit();
}

void MainMenuState::setCallbacks(const std::vector<callback>& callbacks){
    for (auto o : m_GameObjects){
        MenuButton* button = dynamic_cast<MenuButton*>(o);
        if(button){
            button->setCallback(callbacks[button->getCallbackID()]);
        }
    }
}