#ifndef AUDIO_H
#define AUDIO_H

#include "miniaudio.h"

class MultiSound;

class Audio {
public:
    ~Audio();

    static Audio* Instance();

    bool Initialize();

    void PlaySound(unsigned sound);
    void PlaySound(MultiSound* sound);

    void PlayMusic(ma_sound* music);

    ma_engine* GetAudioEngine() { return &engine; }

    void Clear();
private:
    Audio();

    ma_engine engine;

    static Audio* audioInstance;
};

#endif