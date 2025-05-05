#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

#include "Assets.h"
#include "SpriteRenderer.h"

#include <glm.hpp>
#include <string.h>

class Debug : public SpriteRenderer{

private:
    static Debug* DebugInstance;

public:

    static bool debugCollisions;
    static bool debugSprite;

    static Debug* Instance();

    Debug() : SpriteRenderer(ResourceManager::GetShader(Assets::spriteShader), false, false, false) {

    }

    void DrawCircle(vec2 pos_, float rad_);
    void DrawRectangle(vec2 pos_, vec2 size_);
    void Update();
};

#endif