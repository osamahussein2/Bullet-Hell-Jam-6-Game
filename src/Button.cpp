#include "Button.h"
#include "Window.h"
#include "Assets.h"
#include "TextRenderer.h"

void Button::Update()
{   
    UserInterface::Update();

    bool in_rec = CheckRectangle();

    bool pressed = (
        glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS ||
        glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS
    );

    prev_state = state;
    if (in_rec) {
        if (pressed) {
            state = BTN_PRESSED;
        }
        else {
            state = BTN_HOVERED;
            if (prev_state == BTN_DEFAULT){
                Audio::Instance()->PlaySound(Assets::buttonHoverSound);
            }
        }
    }
    else {
        state = BTN_DEFAULT;
    }
}

void Button::Draw(SpriteRenderer& renderer_, vec2 rel_offset_, bool relative_to_game)
{
    color = vec3(1.0);
    vec3 btn_color = vec3(0.7);
    float scale = 1.0;
    switch (state) {
        case BTN_DEFAULT:
            break;
        case BTN_HOVERED:
            color = vec3(0.8941176470588236, 0, 0.34509803921568627);
            btn_color = color;
            scale = 1.3;
            break;
        case BTN_PRESSED:
            color = vec3(0.3);
            btn_color = vec3(0.3);
            break;
    }

    //renderer_.DrawSprite(sprite, position, size, 0.f, color);
    UserInterface::Draw(renderer_, rel_offset_, relative_to_game);
    TextRenderer::Instance()->DrawText(text, position+vec2(size.x/2, size.y/2), scale*size.x/100, true, true, btn_color);
}

bool Button::CheckRectangle()
{
    vec2 mouse_pos = Window::Instance()->GetMousePosition();
    return (
        mouse_pos.x >= position.x && 
        mouse_pos.x <= position.x + size.x &&
        mouse_pos.y >= position.y && 
        mouse_pos.y <= position.y + size.y
    );
}
