#include "TextureManager.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::load(std::string fileName,std::string id,SDL_Renderer* renderer){
    SDL_Surface* tmp_surface = IMG_Load(fileName.c_str());
    if(tmp_surface==nullptr){
        return false;
    }
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,tmp_surface);
    if(texture == nullptr) {
        return false;
    }
    SDL_FreeSurface(tmp_surface);

    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::draw(std::string id,int x,int y,int width,int height,SDL_Renderer* renderer,SDL_RendererFlip flip){
    SDL_Rect source,dist;
    source.x = 0;
    source.y = 0;
    source.w = dist.w = width;
    source.h = dist.h = height;
    dist.x = x;
    dist.y = y;

    SDL_RenderCopyEx(renderer,m_TextureMap[id],&source,&dist,0,0,flip);
}

void TextureManager::drawFrame(std::string id,int x,int y,int width,int height,int cuurrentRow,int currentFrame,SDL_Renderer* renderer,SDL_RendererFlip flip){
    SDL_Rect source,dist;
    source.x = width * currentFrame;
    source.y = height * (cuurrentRow-1);
    source.w = dist.w = width;
    source.h = dist.h = height;
    dist.x = x;
    dist.y = y;

    SDL_RenderCopyEx(renderer,m_TextureMap[id],&source,&dist,0,0,flip);
}
