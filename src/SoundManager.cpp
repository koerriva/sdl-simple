#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::s_Instance = nullptr;

SoundManager::SoundManager(){
    Mix_OpenAudio(22050,AUDIO_S16,2,4096);
}

SoundManager::~SoundManager(){
     Mix_CloseAudio();
}

bool SoundManager::load(std::string fileName,std::string id,sound_type type){
    if(type==SOUND_MUSIC){
        Mix_Music* music = Mix_LoadMUS(fileName.c_str());
        if(music==nullptr){
            std::cerr << "load music error :" << Mix_GetError() << std::endl;
            return false;
        }
        m_music[id] = music;
        return true;
    }
    if(type==SOUND_SFX){
        Mix_Chunk* chunk = Mix_LoadWAV(fileName.c_str());
        if(chunk==nullptr){
            std::cerr << "load wav error :" << Mix_GetError() << std::endl;
            return false;
        }
        m_sfxs[id] = chunk;
        return true;
    }

    std::cerr << "type unsupport!\n";
    return false;
}

void SoundManager::playMusic(std::string id,int loop){
    Mix_PlayMusic(m_music[id],loop);
}

void SoundManager::playSound(std::string id,int loop){
    Mix_PlayChannel(-1,m_sfxs[id],loop);
}