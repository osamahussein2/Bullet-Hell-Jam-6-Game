#ifndef AUDIO_H
#define AUDIO_H

#include "miniaudio.h"

class Audio {
public:
    ~Audio();

    static Audio* Instance();

    bool Initialize();

    void PlaySound(const char* soundPath);

    void PlayMusic(ma_sound* music);

    ma_engine* GetAudioEngine() { return &engine; }

    void Clear();
private:
    Audio();

    ma_engine engine;

    static Audio* audioInstance;
};

#endif