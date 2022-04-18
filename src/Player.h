#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Player : public SDLGameObject
{
public:
    Player();
    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(const LoaderParams* params);

private:
    enum PlayerFace {
        LEFT,RIGHT
    };
    PlayerFace m_playerFace = LEFT;

    RenderOffset renderOffset = {0};

    void handleInput();
};

class PlayerCreator : public BaseCreator {
public:
    GameObject* createGameObject() const  {
        return new Player();
    }
};