#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game
{
private:
    bool m_Running = true;

    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;

    int m_CurrentFrame = 1;

    GameObject* obj;
    GameObject* player;
    GameObject* enemy;

    std::vector<GameObject*> m_GameObjects;
public:
    Game(){};
    ~Game(){};

    bool init(const char* title,int width,int height,bool fullscreen);

    void render();

    void update();

    void handleEnvets();

    void clean();

    bool running() const {return m_Running;}
};