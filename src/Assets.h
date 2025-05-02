#ifndef ASSETS_H
#define ASSETS_H

#include "ResourceManager.h"

enum MusicMapNumbers
{
    anxietyMusic = 0,
};

class Assets{
public:
    // sounds, might not be the best way to do it
    static const char* bip_sound;

public:

    static void LoadAssets();

    static float musicVolume, sfxVolume;

    enum ShaderMapNumbers
    {
        spriteShader = 0
    };

    enum TextureMapNumbers
    {
        playerTexture = 0,
        healthBarTexture = 1,
        currentHealthTexture = 2,
        playerTexture2 = 3,
        textAtlas = 4,
        button = 5,
        sliderBarTexture = 6
    };
};

#endif