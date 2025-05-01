#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "Assets.h"
#include "SpriteRenderer.h"

#include <glm.hpp>
#include <string.h>

class TextRenderer : public SpriteRenderer{

private:
    static TextRenderer* TextRendererInstance;

    unsigned atlas;

    int letW = 8;
    int letH = 16;

public:

    static TextRenderer* Instance();

    TextRenderer(unsigned atlas_, Shader shader_) : atlas(atlas_), SpriteRenderer(shader_, false, false, true) {
        
        GetAnimationHandler()->AddAnimation( AnimationData{
            13, // columns
            4, // rows
            0, // y_pos
            60, // frames
            5.f // fps
            }   
        );
        
    }

    void DrawChar(char letter, float x, float y, float w, float h);
    void DrawText(const char* text, vec2 pos, float scale);

};

#endif