#pragma once

#include "GameState.h"
#include "GameObject.h"
#include <vector>

class MenuState : public GameState
{
protected:
    typedef void(*callback)();

    virtual void setCallbacks(const std::vector<callback>& callbacks) = 0;

    std::vector<callback> m_callbacks;
};

class MainMenuState : public MenuState
{
private:
    static const std::string s_MenuID;

    std::vector<GameObject*> m_GameObjects;

    static void s_menuToPlay();
    static void s_exitFromMenu();

    virtual void setCallbacks(const std::vector<callback>& callbacks);
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {return s_MenuID;}
};