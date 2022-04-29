#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public ShooterObject
{
public:
    AnimatedGraphic();
    virtual void update();
    virtual void draw();
    virtual void clean();

    virtual void load(std::unique_ptr<LoaderParams> const& params);

private:
    int m_animSpeed = 10;
};

class AnimatedGraphicCreator : public BaseCreator {
public:
    GameObject* createGameObject() const {
        return new AnimatedGraphic();
    }
};
