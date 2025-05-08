#ifndef ASSETS_H
#define ASSETS_H

#include "ResourceManager.h"

class Assets{
public:
    // sounds, might not be the best way to do it
    //static const char* bip_sound;

public:

    static void LoadAssets();

    static float musicVolume, sfxVolume;

    enum ShaderMapNumbers
    {
        spriteShader = 0,
        backgroundShader = 1
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

        bombaTexture = 8,
        cultistBasicTexture = 9,
        summonerTexture = 10,
        orbTexture = 11,

        auraUITexture = 12,
        auraBarTexture = 13,
        scoreUITexture = 14,
        
        progressBarUnit = 15,
        progressBarBoss = 16,
        progressBarPoint = 17,

        enemyHealthTexture = 18,
        beholderTexture = 19,

        //Debug textures
        circleTexture = 999,
        rectangleTexture = 1000
    };

    enum MusicMapNumbers
    {
        anxietyMusic = 0,
        LTHAWFD = 1,
        MainMenu = 2,
        HellHole = 3
    };
    
    enum SoundMapNumbers
    {
        buttonHoverSound = 0,
    };

};

#endif