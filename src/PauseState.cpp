#include "PauseState.h"
#include "Game.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "StateParser.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain(){
    Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay(){
    Game::Instance()->getStateMachine()->popState();
}

void PauseState::update(){
    for (auto o : m_GameObjects)
    {
        o->update();
    }
}

void PauseState::render(){
    for (auto o : m_GameObjects){
        o->draw();
    }
}

bool PauseState::onEnter(){
    std::cout << "entring PauseState" << std::endl;

    // auto textureManager = TextureManager::Instance();
    // auto renderer = Game::Instance()->getRenderer();

    // textureManager->load("data/Menu_Button.png","menu_button",renderer);
    // textureManager->load("data/Resume_Button.png","resume_button",renderer);

    // GameObject* menu_button = new MenuButton(new LoaderParams(340,150,600,200,"menu_button"),s_pauseToMain);
    // GameObject* resume_button = new MenuButton(new LoaderParams(340,370,600,200,"resume_button"),s_resumePlay);

    // m_GameObjects.push_back(menu_button);
    // m_GameObjects.push_back(resume_button);
    StateParser stateParser;
    stateParser.parseState("game.xml",s_pauseID,&m_GameObjects,&m_textureIDs);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);
    setCallbacks(m_callbacks);

    return true;
}

bool PauseState::onExit(){
    std::cout << "exiting PauseState" << std::endl;
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

void PauseState::setCallbacks(const std::vector<callback>& callbacks){
    for (auto o : m_GameObjects){
        MenuButton* button = dynamic_cast<MenuButton*>(o);
        if(button){
            button->setCallback(callbacks[button->getCallbackID()]);
        }
    }
}