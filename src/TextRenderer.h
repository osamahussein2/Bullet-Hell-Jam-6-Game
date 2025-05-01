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
            5, // rows
            0, // y_pos
            65, // frames
            5.f // fps
            }   
        );
        
    }

    void DrawChar(char letter, float x, float y, float w, float h);
    void DrawText(const char* text, vec2 pos, float scale, bool centered_h = false, bool centered_v = false);
    
    void DrawTextRelCent(const char* text, vec2 rel_pos, float rel_scale);

    vec2 GetCharacterSize() { return vec2(letW, letH); }

};

#endif