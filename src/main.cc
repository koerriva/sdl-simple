#define SDL_MAIN_HANDLED

#include <iostream>
#include "Game.h"

int main(int argc,char** argv){
    std::cout << "hello sdl2" << std::endl;

    bool r = Game::Instance()->init("wx",1280,720,0);

    if(r){
        std::cout << "Enjoy!" << std::endl;
    }

    while(Game::Instance()->running()){
        Game::Instance()->handleEnvets();
        Game::Instance()->update();
        Game::Instance()->render();

        SDL_Delay(10);
    }

    Game::Instance()->clean();
    return 0;
}