#pragma once

#include "GameObject.h"
#include <glm/glm.hpp>

using namespace glm;

class SDLGameObject : public GameObject
{
protected:
    ivec2 m_position;
    ivec2 m_velocity;
    ivec2 m_acceleration;

    int m_width,m_height;
    int m_currentFrame,m_currentRow;
    std::string m_textureID;
public:
    SDLGameObject(const LoaderParams* params);

    virtual void draw();
    virtual void update();
    virtual void clean();
};
