#ifndef __SoundManager__
#define __SoundManager__

#include <iostream>
#include <map>
#include <string>
#include <SDL2/SDL_mixer.h>

using namespace std;

enum sound_type
{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager
{
private:
    static SoundManager* instance;
    map<string, Mix_Chunk*> m_sfxs;
    map<string, Mix_Music*> m_music;
    SoundManager();
    ~SoundManager();
public:
    static SoundManager* Instance()
    {
        if(instance == 0)
        {
            instance = new SoundManager();
            return instance;
        }
        return instance;
    }
    bool load(string fileName, string id, sound_type type);
    void playSound(string id, int loop);
    void playMusic(string id, int loop);
};

typedef SoundManager TheSoundManager;

#endif
