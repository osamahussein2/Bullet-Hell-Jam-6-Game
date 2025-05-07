#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include "miniaudio.h"
#include "Audio.h"

/*
There is a better way to do all that with decoding audio data and using for every alias
*/

class Music {
public:

    ma_sound* GetSound() { return &music; }
    
    void Load(const char* file) {
        ma_result result = ma_sound_init_from_file(
            Audio::Instance()->GetAudioEngine(),
            file,
            MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_LOOPING,
            NULL,
            NULL,
            &music
        );
    
        if (result != MA_SUCCESS) {
            std::cerr << "Failed to load music file: " << file << std::endl;
        }
    }

    void FullStop() {
        ma_sound_seek_to_pcm_frame(&music, 0);
        ma_sound_stop(&music);
    }

    void Stop() {
        ma_sound_stop(&music);
    }

    void PlayFromStart() {
        ma_sound_seek_to_pcm_frame(&music, 0);
        Play();
    }

    void Play() {
        ma_sound_start(&music);
    }

    void Unload() {
        ma_sound_uninit(&music);
    }

    void SetIndividualVolumeCoeff(float coeff) {
        individualVolume = coeff;
    }

    void SetVolume(float volume) {
        ma_sound_set_volume(&music, individualVolume*volume);
    }

private:

    float individualVolume = 1.0;
    ma_sound music;
};

#endif