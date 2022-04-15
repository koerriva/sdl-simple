// #define SDL_MAIN_HANDLED
#include <SDL2/SDL_main.h>
#include <iostream>
#include "Game.h"
#include "Base64.h"

int main(int argc,char** argv){
    // std::string test = "ABC123Test Lets Try this' input and see What \"happens\"";
    // Base64 base64;

    // std::string encodeText = base64.encode(test,test.size());
    // std::cout << encodeText << std::endl;

    // std::string decodeText = base64.decode(encodeText,encodeText.size()+1);
    // std::cout << decodeText << std::endl;

    std::cout << "hello sdl2\n";

    bool r = Game::Instance()->init("wx",1280,800,0);

    if(r){
        std::cout << "Enjoy!\n";
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