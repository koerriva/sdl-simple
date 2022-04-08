#pragma once

#include "GameObject.h"

class SDLGameObject : public GameObject
{
protected:
    int m_x,m_y;
    int m_width,m_height;
    int m_currentFrame,m_currentRow;
    std::string m_textureID;
public:
    SDLGameObject(const LoaderParams* params);
    
    virtual void draw();
    virtual void update();
    virtual void clean();
};
