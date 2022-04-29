#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public ShooterObject
{
public:
    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(std::unique_ptr<LoaderParams> const& params);
    virtual std::string type() { return "Enemy"; }

protected:
    int m_health;

    Enemy();
    virtual ~Enemy(){}

    friend class EnemyCreator;
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
