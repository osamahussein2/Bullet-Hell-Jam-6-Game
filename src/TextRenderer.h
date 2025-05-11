#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "Assets.h"
#include "SpriteRenderer.h"

#include <glm.hpp>
#include <string.h>

struct AnimatedText{

    std::string text = "This is the default text of the AnimatedText struct";
    float speed = 15.f;
    float frame_counter = 0;

    //AnimatedText(std::string Text, float Speed) : text(Text), speed(Speed){};

    bool IsDone(){
        return int(frame_counter) >= strlen(text.c_str());
    }

    void Complete(){
        frame_counter = strlen(text.c_str());
    }

    void Update(float deltaTime, float speed_coef = 1.f){
        if (!IsDone()){
            frame_counter += deltaTime * speed * speed_coef;

            if (text[int(frame_counter)-1] == ','){
                frame_counter -= deltaTime * speed * speed_coef / 1.2;
            }
            if (text[int(frame_counter)-1] == '.'){
                frame_counter -= deltaTime * speed * speed_coef / 1.1;
            }
        }
    }

    std::string GetCurrentText(){
        return text.substr(0, frame_counter);;
    }

};

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

    void DrawChar(char letter, float x, float y, float w, float h, vec3 color = vec3(1.0));
    void DrawText(const char* text, vec2 pos, float scale, bool centered_h = false, bool centered_v = false, vec3 color = vec3(1.0));
    void DrawTextFromRight(const char* text, vec2 pos, float scale, bool centered_v = false, vec3 color = vec3(1.0));
    void DrawTextWrap(const char* text, vec2 pos, vec2 size, float scale, vec3 color = vec3(1.0));

    void DrawTextRelCent(const char* text, vec2 rel_pos, float rel_scale, vec3 color = vec3(1.0));
    void DrawTextRelFromRight(const char* text, vec2 rel_pos, float rel_scale, vec3 color = vec3(1.0));
    void DrawTextRelWrap(const char* text, vec2 rel_pos, vec2 rel_size, float rel_scale, vec3 color = vec3(1.0));

    vec2 GetCharacterSize() { return vec2(letW, letH); }
};

#endif