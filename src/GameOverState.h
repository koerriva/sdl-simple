#pragma once

#include "GameState.h"
#include "MenuState.h"
#include <vector>

class GameObject;

class GameOverState : public MenuState
{
private:
    /* data */
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {return s_GameOverID;}

private:
    static void s_gameOverToMain();
    static void s_restartPlay();

    static const std::string s_GameOverID;

    std::vector<GameObject*> m_GameObjects;

    virtual void setCallbacks(const std::vector<callback>& callbacks);
};
