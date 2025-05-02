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
                Audio::Instance()->PlaySound(Assets::bip_sound);
            }
        }
    }
    else {
        state = BTN_DEFAULT;
    }
}

void Button::Draw(SpriteRenderer& renderer_)
{
    color = vec3(1.0);
    float scale = 1.0;
    switch (state) {
        case BTN_DEFAULT:
            color = vec3(1.0);
            break;
        case BTN_HOVERED:
            color = vec3(0.7);
            scale = 1.3;
            break;
        case BTN_PRESSED:
            color = vec3(0.3);
            break;
    }

    renderer_.DrawSprite(sprite, position, size, 0.f, color);
    TextRenderer::Instance()->DrawText(text, position+vec2(size.x/2, size.y/2), scale*size.x/100, true, true);
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
