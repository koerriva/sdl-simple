#pragma once

#include "GameState.h"
#include "GameObject.h"
#include "SDLGameObject.h"
#include "Level.h"
#include <vector>

class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {return s_playID;}
private:
    static const std::string s_playID;

    Level* m_currentLevel = nullptr;

    std::vector<GameObject*> m_GameObjects;

    bool checkCollision(SDL_Rect* r1,SDL_Rect* r2);
};
