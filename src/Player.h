#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject
{
public:
    Player();
    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(std::unique_ptr<LoaderParams> const& params);

    virtual std::string type() { return "Player"; }

private:
    enum PlayerFace {
        LEFT,RIGHT
    };
    PlayerFace m_playerFace = LEFT;

    RenderOffset renderOffset = {0};

    void ressurect();
    void handleInput();
    void handleAnimation();

    int m_invulnerable;
    int m_invulnerableTime;
    int m_invulnerableCounter;
};

class PlayerCreator : public BaseCreator {
public:
    GameObject* createGameObject() const  {
        return new Player();
    }
};