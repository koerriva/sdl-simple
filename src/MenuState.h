#pragma once

#include "GameState.h"
#include "GameObject.h"
#include <vector>

class MenuState : public GameState
{
private:
    static const std::string s_MenuID;

    std::vector<GameObject*> m_GameObjects;

    static void s_menuToPlay();
    static void s_exitFromMenu();
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {return s_MenuID;}
};