#include "TextureManager.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::load(std::string fileName,std::string id,SDL_Renderer* renderer){
    if(m_TextureMap[id]!=nullptr){
        return m_TextureMap[id];
    }
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

void TextureManager::draw(std::string id,int x,int y,int width,int height,SDL_Renderer* renderer,SDL_RendererFlip flip,RenderOffset renderOffset){
    SDL_Rect source,dist;
    source.x = 0;
    source.y = 0;
    source.w = dist.w = width;
    source.h = dist.h = height;
    dist.x = x - renderOffset.spriteOffsetX;
    dist.y = y - renderOffset.spriteOffsetY;

    SDL_RenderCopyEx(renderer,m_TextureMap[id],&source,&dist,0,0,flip);
}

void TextureManager::drawFrame(std::string id,int x,int y,int width,int height,int currentRow,int currentFrame,SDL_Renderer* renderer,SDL_RendererFlip flip,RenderOffset renderOffset){
    SDL_Rect source,dist;
    source.x = width * currentFrame;
    source.y = height * (currentRow-1);
    source.w = dist.w = width;
    source.h = dist.h = height;
    dist.x = x - renderOffset.spriteOffsetX;
    dist.y = y - renderOffset.spriteOffsetY;

    SDL_RenderCopyEx(renderer,m_TextureMap[id],&source,&dist,0,0,flip);
}

void TextureManager::drawTile(std::string id,int margin,int spacing,int x,int y,int width,int height,int currentRow,int currentColumn,SDL_Renderer* renderer){
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentColumn;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(renderer,m_TextureMap[id],&srcRect,&destRect,0,0,SDL_FLIP_NONE);
}

void TextureManager::clearFromTextureMap(std::string id){
    m_TextureMap.erase(id);
}