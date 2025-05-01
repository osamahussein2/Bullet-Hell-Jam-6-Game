#ifndef ASSETS_H
#define ASSETS_H

#include "ResourceManager.h"

class Assets{
public:
    // sounds, might not be the best way to do it
    static const char* bip_sound;

public:

    static void LoadAssets();

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
		playButton = 4,
		quitButton = 5,
		yesButton = 6,
		noButton = 7,
		quitConfirmationText = 8,
        resumeButton = 9,
        gamePauseText = 10,
        quitToMainMenuConfirmationText = 11,
        textAtlas = 12
    };

    enum MusicMapNumbers
    {
        anxietyMusic = 0,
    };
};

#endif