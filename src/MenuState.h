#pragma once

#include "GameState.h"

class MenuState : public GameState
{
private:
    static const std::string s_menuID;
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {return s_menuID;}
};