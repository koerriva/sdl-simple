#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <unordered_map>

class TextureManager
{
private:
    std::unordered_map<std::string,SDL_Texture*> m_TextureMap;

    TextureManager(){};

    static TextureManager* s_Instance;
public:
    
    ~TextureManager(){};

    bool load(std::string fileName,std::string id,SDL_Renderer* renderer);

    void draw(std::string id,int x,int y,int width,int height,SDL_Renderer* renderer,SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(std::string id,int x,int y,int width,int height,int currentRow,int currentFrame,SDL_Renderer* renderer,SDL_RendererFlip flip = SDL_FLIP_NONE);

    void clearFromTextureMap(std::string id);

    static TextureManager* Instance() {
        if(s_Instance==nullptr){
            s_Instance = new TextureManager();
        }

        return s_Instance;
    };
};
