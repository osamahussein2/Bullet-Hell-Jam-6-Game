#ifndef MULTI_SOUND_H
#define MULTI_SOUND_H

#include <iostream>
#include "miniaudio.h"
#include "Audio.h"

constexpr int MAX_ALIASES = 5;

/*
There is a better way to do all that with decoding audio data and using for every alias
*/

class MultiSound {
public:

    bool Load(const char* file) {
        for (int i = 0; i < MAX_ALIASES; i++) {
            if (!LoadSound(file, i)) {
                return false;
            }
        }
        return true;
    }

    void Play() {
        for (int i = 0; i < MAX_ALIASES; i++){
            if (!ma_sound_is_playing(&aliases[i])) {
                ma_sound_start(&aliases[i]);
                break;
            }
        }
    }
    void Unload() {
        for (ma_sound alias : aliases) {
            ma_sound_uninit(&alias);
        }
    }

    void SetIndividualVolumeCoeff(float coeff) {
        individualVolume = coeff;
    }

    void SetVolume(float volume) {
        for (ma_sound& alias : aliases) {
            ma_sound_set_volume(&alias, volume*individualVolume);
        }
    }

private:
    float individualVolume = 1.0f;
    bool LoadSound(const char* file, int index) {
        ma_result result = ma_sound_init_from_file(
            Audio::Instance()->GetAudioEngine(),
            file,
            MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC,
            NULL,
            NULL,
            &aliases[index]
        );
        
        if (result != MA_SUCCESS) {
            std::cerr << "Failed to load sound alias: " << file << std::endl;
            return false;
        }
        return true;
    }

    ma_sound aliases[MAX_ALIASES];
};


#endif