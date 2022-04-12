#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"

#include <iostream>

const std::string MenuState::s_MenuID = "MENU";

void MenuState::update(){
    for (auto const o : m_GameObjects)
    {
        o->update();
    }
}

void MenuState::render(){
    for (auto const o : m_GameObjects)
    {
        o->draw();
    }
}

bool MenuState::onEnter(){
    std::cout << "entring MenuState" << std::endl;

    auto textureManager = TextureManager::Instance();
    auto renderer = Game::Instance()->getRenderer();

    textureManager->load("data/Play_Button.png","plan_button",renderer);
    textureManager->load("data/Exit_Button.png","exit_button",renderer);

    GameObject* plan_button = new MenuButton(new LoaderParams(340,150,600,200,"plan_button"),s_menuToPlay);
    GameObject* exit_button = new MenuButton(new LoaderParams(340,370,600,200,"exit_button"),s_exitFromMenu);

    m_GameObjects.push_back(plan_button);
    m_GameObjects.push_back(exit_button);

    return true;
}

bool MenuState::onExit(){
    std::cout << "exiting MenuState" << std::endl;
    for (auto const o : m_GameObjects)
    {
        o->clean();
    }
    m_GameObjects.clear();

    auto textureManager = TextureManager::Instance();
    textureManager->clearFromTextureMap("plan_button");
    textureManager->clearFromTextureMap("plan_col_button");
    textureManager->clearFromTextureMap("exit_button");
    textureManager->clearFromTextureMap("exit_col_button");

    return true;
}

void MenuState::s_menuToPlay(){
    std::cout << "menu to play" << std::endl;
}

void MenuState::s_exitFromMenu(){
    std::cout << "exit from menu" << std::endl;
}