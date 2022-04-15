#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "GameStateMachine.h"

#include <vector>

class Game
{
private:
    bool m_Running = true;

    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;

    Game(){};
    static Game* s_Instance;

    GameStateMachine* m_GameStateMachine;

    int m_width,m_height;
public:
    
    ~Game(){};

    bool init(const char* title,int width,int height,bool fullscreen);

    void render();

    void update();

    void handleEnvets();

    void clean();

    bool running() const {return m_Running;}

    void quit();

    GameStateMachine* getStateMachine() { return m_GameStateMachine; }

    static Game* Instance(){
        if(s_Instance==nullptr){
            s_Instance = new Game();
        }

        return s_Instance;
    }

    SDL_Renderer* getRenderer() const {return m_Renderer;}

    int getGameWidth() const { return m_width; }
    int getGameHeight() const { return m_height; }
};