#ifndef BUTTON_H
#define BUTTON_H

#include "UserInterface.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

enum ButtonState {
    BTN_DEFAULT = 0,
    BTN_HOVERED = 1,
    BTN_PRESSED = 2
};

class Button : public UserInterface{

public:
    ButtonState prev_state = BTN_DEFAULT;
    ButtonState state = BTN_DEFAULT;
    const char* text;

public:
    Button(vec2 rel_pos_, vec2 rel_size_, unsigned int sprite_, unsigned int shader_, const char* text_) : // ui size and pos are relative to window
    UserInterface(rel_pos_, rel_size_, sprite_, shader_, vec3(1.0)), text(text_) {
    }

    void Update();
    virtual void Draw(SpriteRenderer& renderer_, vec2 rel_offset_ = vec2(0.0), bool relative_to_game = false) override;

    bool CheckRectangle();
    ButtonState GetState() { return state; }
    ButtonState GetPreviousState() { return prev_state; }
};

#endif