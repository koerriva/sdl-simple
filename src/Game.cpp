#include <iostream>
#include "Game.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"

Game* Game::s_Instance = nullptr;

bool Game::init(const char* title,int width,int height,bool fullscreen){
    int r = SDL_Init(SDL_INIT_EVERYTHING);
    if(r<0)return false;

    m_width = width;
    m_height = height;

    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    flags |= SDL_WINDOW_SHOWN;

    m_Window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,flags);
    m_Renderer = SDL_CreateRenderer(m_Window,-1,0);
    SDL_SetRenderDrawColor(m_Renderer,186,204,217,255);//云水蓝
    SDL_RenderClear(m_Renderer);

    InputHandler::Instance()->initialiseJoysticks();

    GameObjectFactory::Instance()->registerType("MenuButton",new MenuButtonCreator());
    GameObjectFactory::Instance()->registerType("Player",new PlayerCreator());
    GameObjectFactory::Instance()->registerType("Enemy",new EnemyCreator());
    GameObjectFactory::Instance()->registerType("AnimatedGraphic",new AnimatedGraphicCreator());

    m_GameStateMachine = new GameStateMachine();
    m_GameStateMachine->changeState(new MainMenuState());

    m_Running = true;
    return true;
}

void Game::render(){
    SDL_SetRenderDrawColor(m_Renderer,186,204,217,255);//云水蓝
    SDL_RenderClear(m_Renderer);

    m_GameStateMachine->render();
    
    SDL_RenderPresent(m_Renderer);
}

void Game::update(){
    m_GameStateMachine->update();
}

void Game::clean(){
    InputHandler::Instance()->clean();
}

void Game::quit(){
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();

    m_Running = false;
}

void Game::handleEnvets(){
    auto ih = InputHandler::Instance();
    ih->update();

    if(ih->isKeyDown(SDL_SCANCODE_RETURN)){
        m_GameStateMachine->changeState(new PlayState());
    }
}