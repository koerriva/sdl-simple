#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{
public:
    Enemy();
    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(const LoaderParams* params);

private:
    enum EnemyFace {
        LEFT,RIGHT
    };
    EnemyFace m_enemyFace = RIGHT;
};


class EnemyCreator : public BaseCreator {
public:
    GameObject* createGameObject() const  {
        return new Enemy();
    }
};
