#pragma once

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic(const LoaderParams* params,int animSpeed=10);
    virtual void update();
    virtual void draw();
    virtual void clean();

private:
    int m_animSpeed = 1;
};
