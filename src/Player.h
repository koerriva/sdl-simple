#pragma once

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
    Player(const LoaderParams* params);
    virtual void draw();
    virtual void update();
    virtual void clean();

private:
    enum PlayerFace {
        LEFT,RIGHT
    };
    PlayerFace m_playerFace = LEFT;

    void handleInput();
};
