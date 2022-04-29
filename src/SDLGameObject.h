#pragma once

#include "GameObject.h"
#include <glm/glm.hpp>

using namespace glm;

class ShooterObject : public GameObject
{
protected:
    ShooterObject();

    //animation
    void doDyingAnimation();

    
    int m_bulletFiringSpeed = 0;
    int m_bulletCounter = 0;
    int m_moveSpeed = 0;

    int m_dyingTime = 0;
    int m_dyingCounter = 0;

    bool m_playedDeathSound = false;
public:
    virtual ~ShooterObject(){};

    virtual void load(std::unique_ptr<LoaderParams> const& params);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void collision();
    virtual std::string type() { return "SDLGameObject"; }
};
