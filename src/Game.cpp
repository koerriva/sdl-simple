#include "Game.h"
#include <iostream>

Game* Game::s_Instance = nullptr;

bool Game::init(const char* title,int width,int height,bool fullscreen){
    int r = SDL_Init(SDL_INIT_EVERYTHING);
    if(r<0)return false;

    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    flags |= SDL_WINDOW_SHOWN;

    m_Window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,flags);
    m_Renderer = SDL_CreateRenderer(m_Window,-1,0);
    SDL_SetRenderDrawColor(m_Renderer,120,40,30,200);

    TextureManager::Instance()->load("data/animate-alpha.png","animate",m_Renderer);
    TextureManager::Instance()->load("data/Knight_Idle.png","knight-idle",m_Renderer);
    TextureManager::Instance()->load("data/Knight_Run.png","knight-run",m_Renderer);

    m_Running = true;

    player = new Player(new LoaderParams(300,300,120,80,"knight-run"));
    enemy = new Enemy(new LoaderParams(0,0,128,82,"animate"));

    m_GameObjects.push_back(player);
    m_GameObjects.push_back(enemy);

    return true;
}

void Game::render(){
    SDL_RenderClear(m_Renderer);

    //draw someting
    for (auto const o : m_GameObjects)
    {
        o->draw();
    }
    

    SDL_RenderPresent(m_Renderer);
}

void Game::update(){
    for (auto const o : m_GameObjects)
    {
        o->update();
    }
    
}

void Game::clean(){
    for (auto const o : m_GameObjects)
    {
        o->draw();
    }
    
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Game::handleEnvets(){
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            m_Running = false;
            break;
        
        default:
            break;
        }
    }
}