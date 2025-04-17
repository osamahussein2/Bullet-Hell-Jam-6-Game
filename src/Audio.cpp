#include "Audio.h"
#include <iostream>

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

void Audio::PlaySound(const char* soundPath){
    ma_result result = ma_engine_play_sound(&engine, soundPath, NULL);
}

Audio* Audio::Instance() {
    if (audioInstance == nullptr) {
        audioInstance = new Audio();
    }
    return audioInstance;
}

