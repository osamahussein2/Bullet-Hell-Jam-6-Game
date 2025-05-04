#include "Audio.h"
#include <iostream>
#include "MultiSound.h"
#include "ResourceManager.h"

Audio* Audio::audioInstance = nullptr;

bool Audio::Initialize(){
    ma_result result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS){
        std::cerr << "ma_engine_init() failed\n";
        return false;
    }
    return true;
}

Audio::Audio(){}

Audio::~Audio(){}

void Audio::PlaySound(unsigned sound)
{
    PlaySound(ResourceManager::GetSound(sound));
}

void Audio::PlaySound(MultiSound *sound)
{
    sound->Play();
}

void Audio::PlayMusic(ma_sound* music){
    ma_sound_start(music);
}

Audio* Audio::Instance() {
    if (audioInstance == nullptr) {
        audioInstance = new Audio();
    }
    return audioInstance;
}

void Audio::Clear(){
    ma_engine_uninit(&engine);
}