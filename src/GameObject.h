#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <memory>
#include <glm/glm.hpp>

using namespace glm;

struct RenderOffset
{
    int spriteOffsetX=0;
    int spriteOffsetY=0;
    int animOffsetX=0;
    int animOffsetY=0;
};

class LoaderParams {
public:
    LoaderParams(int x,int y,int width,int height,std::string textureID,int numFrames=1,int animSpeed=10,int callbackID=0
        ,SDL_Rect collision={0},int spriteOffsetX=0,int spriteOffsetY=0){
        this->m_x = x;
        this->m_y = y;
        this->m_width = width;
        this->m_height = height;
        this->m_textureID = textureID;
        this->m_numFrames = numFrames;
        this->m_animSpeed = animSpeed;
        this->m_callbackID = callbackID;
        this->m_collision = collision;
        this->m_spriteOffsetX = spriteOffsetX;
        this->m_spriteOffsetY = spriteOffsetY;
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
    int getSpriteOffsetX() const {return m_spriteOffsetX;}
    int getSpriteOffsetY() const {return m_spriteOffsetY;}
    
private:
    int m_x,m_y;
    int m_width,m_height;
    int m_numFrames;
    std::string m_textureID;

    int m_animSpeed;
    int m_callbackID;

    SDL_Rect m_collision;

    int m_spriteOffsetX,m_spriteOffsetY;
};

class GameObject
{
public:

    virtual void load(std::unique_ptr<LoaderParams> const& params) = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
    virtual void collision() = 0;
    virtual std::string type() = 0;

    //movement
    ivec2 getPosition() { return m_position; }
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }

    //scroll
    void scroll(int scrollspeed) {
        m_position.x -= scrollspeed;
    }

    //play state
    bool updating() { return m_updating; }
    bool dead() { return m_dead; }
    bool dying() { return m_dying; }
    void setUpdating(bool updating) {
        m_updating = updating;
    }

    //physics
    SDL_Rect* getCollision() {
        return &m_collision;
    }

protected:
    GameObject():m_position(0,0)
        ,m_velocity(0,0)
        ,m_acceleration(0,0)
        ,m_width(0)
        ,m_height(0)
        ,m_currentRow(1)
        ,m_currentFrame(1)
        ,m_updating(false)
        ,m_dead(false)
        ,m_dying(false)
        ,m_angle(0)
        ,m_alpha(255)
        , m_collision({0})
        {}
    virtual ~GameObject(){}

    //movement
    ivec2 m_position = {0,0};
    ivec2 m_velocity = {0,0};
    ivec2 m_acceleration = {0,0};

    //size
    int m_width = 0,m_height = 0;
    
    //animation
    int m_currentFrame = 1,m_currentRow=1;
    int m_numFrames = 1;
    std::string m_textureID;

    //physics
    SDL_Rect m_collision;

    //common state
    bool  m_updating = false;
    bool m_dead = false;
    bool m_dying = false;

    //rotation
    int m_angle = 0;
    //blending
    int m_alpha = 255;
};
