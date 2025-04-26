#ifndef ASSETS_H
#define ASSETS_H

#include "ResourceManager.h"

class Assets{
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
		quitConfirmationText = 8
    };

    enum MusicMapNumbers
    {
        anxietyMusic = 0,
    };
};

#endif