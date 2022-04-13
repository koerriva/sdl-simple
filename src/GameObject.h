#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class LoaderParams {
public:
    LoaderParams(int x,int y,int width,int height,std::string textureID,int numFrames=1){
        this->m_x = x;
        this->m_y = y;
        this->m_width = width;
        this->m_height = height;
        this->m_textureID = textureID;
        this->m_numFrames = numFrames;
    }

    int getX() const {return m_x;}
    int getY() const {return m_y;}
    int getWidth() const {return m_width;}
    int getHeight() const {return m_height;}
    int getNumFrames() const {return m_numFrames;}
    std::string getTextureID() const {return m_textureID;}
    
private:
    int m_x,m_y;
    int m_width,m_height;
    int m_numFrames;
    std::string m_textureID;
};

class GameObject
{
public:

    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

protected:
    GameObject(const LoaderParams* params){}
    virtual ~GameObject(){}
};
