#ifndef BACKGROUND_RENDERER_H
#define BACKGROUND_RENDERER_H

#include "Assets.h"
#include "SpriteRenderer.h"

#include <glm.hpp>
#include <string.h>

class BackgroundRenderer : public SpriteRenderer {
private:
    static BackgroundRenderer* BackgroundRendererInstance;

public:
    BackgroundRenderer();

    static BackgroundRenderer* Instance();
    void DrawBackground(glm::vec2 size);
};

#endif