#ifndef AUDIO_H
#define AUDIO_H

#include "miniaudio.h"

class Audio {
public:
    ~Audio();

    static Audio* Instance();

    bool Initialize();

    void PlaySound(const char* soundPath);

private:
    Audio();

    ma_engine engine;

    static Audio* audioInstance;
};

#endif