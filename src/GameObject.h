#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class GameObject
{
protected:
    int m_x,m_y;
    int m_width,m_height;
    int m_currentFrame,m_currentRow;
    std::string m_textureID;

public:

    virtual void load(int x,int y,int width,int height,std::string textureId);
    virtual void draw(SDL_Renderer* renderer);
    virtual void update();
    virtual void clean();
};
