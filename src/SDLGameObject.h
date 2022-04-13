#pragma once

#include "GameObject.h"
#include <glm/glm.hpp>

using namespace glm;

class SDLGameObject : public GameObject
{
protected:
    ivec2 m_position{0,0};
    ivec2 m_velocity{0,0};
    ivec2 m_acceleration{0,0};

    int m_width = 0,m_height = 0;
    int m_currentFrame = 1,m_currentRow=1;
    int m_numFrames = 1;

    SDL_Rect m_collisionRect;

    std::string m_textureID;
public:
    SDLGameObject(const LoaderParams* params);

    virtual void draw();
    virtual void update();
    virtual void clean();

    ivec2 getPosition() const {return m_position;}
    ivec2 getSize() const {return ivec2{m_width,m_height};}

    SDL_Rect* getCollisionRect() {return &m_collisionRect;}
};
