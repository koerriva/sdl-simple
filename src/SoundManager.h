#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "SDL2/SDL_mixer.h"

enum sound_type {
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager
{
private:
    static SoundManager* s_Instance;

    std::unordered_map<std::string,Mix_Chunk*> m_sfxs;
    std::unordered_map<std::string,Mix_Music*> m_music;

    SoundManager();
    ~SoundManager();

    SoundManager(const SoundManager&);
    SoundManager &operator=(const SoundManager&);
public:

    static SoundManager* Instance(){
        if(s_Instance==nullptr){
            s_Instance = new SoundManager();
        }
        return s_Instance;
    }

    bool load(std::string fileName,std::string id,sound_type type);

    void playSound(std::string id,int loop);
    void playMusic(std::string id,int loop);
};