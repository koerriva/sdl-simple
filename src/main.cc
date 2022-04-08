#define SDL_MAIN_HANDLED

#include <iostream>
#include "Game.h"

int main(int argc,char** argv){
    std::cout << "hello sdl2" << std::endl;
    Game* game = new Game();
    bool r = game->init("NodeEditor",1280,720,0);

    if(r){
        std::cout << "Enjoy!" << std::endl;
    }

    while(game->running()){
        game->handleEnvets();
        game->update();
        game->render();

        SDL_Delay((1/60.0f)*1000);
    }

    game->clean();
    return 0;
}