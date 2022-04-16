#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class LoaderParams {
public:
    LoaderParams(int x,int y,int width,int height,std::string textureID,int numFrames=1,int animSpeed=10,int callbackID=0
        ,SDL_Rect collision={0}){
        this->m_x = x;
        this->m_y = y;
        this->m_width = width;
        this->m_height = height;
        this->m_textureID = textureID;
        this->m_numFrames = numFrames;
        this->m_animSpeed = animSpeed;
        this->m_callbackID = callbackID;
        this->m_collision = collision;
    }

    int getX() const {return m_x;}
    int getY() const {return m_y;}
    int getWidth() const {return m_width;}
    int getHeight() const {return m_height;}
    int getNumFrames() const {return m_numFrames;}
    std::string getTextureID() const {return m_textureID;}
    int getAnimSpeed() const {return m_animSpeed;}
    int getCallbackID() const {return m_callbackID;}
    SDL_Rect getCollision() const {return m_collision;}
    
private:
    int m_x,m_y;
    int m_width,m_height;
    int m_numFrames;
    std::string m_textureID;

    int m_animSpeed;
    int m_callbackID;

    SDL_Rect m_collision;
};

class GameObject
{
public:

    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

    //load
    virtual void load(const LoaderParams* params) = 0;

protected:
    GameObject(){}
    virtual ~GameObject(){}
};
