#ifndef ASSETS_H
#define ASSETS_H

#include "ResourceManager.h"

enum MusicMapNumbers
{
    anxietyMusic = 0,
};

enum SoundMapNumbers
{
    buttonHoverSound = 0,
};

class Assets{
public:
    // sounds, might not be the best way to do it
    //static const char* bip_sound;

public:

    static void LoadAssets();

    static float musicVolume, sfxVolume;

    enum ShaderMapNumbers
    {
        spriteShader = 0
    };

    enum TextureMapNumbers
    {
        textAtlas = 0,
        buttonTexture = 1,
        sliderBarTexture = 2,

        playerTexture = 3,

        healthBarTexture = 4,
        currentHealthTexture = 5,
        
        playerBulletTexture = 6,
        enemyBulletTexture = 7,
        
    };
};

#endif