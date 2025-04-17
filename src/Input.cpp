#include "Input.h"

std::array<char, GLFW_KEY_LAST + 1> Input::currentKeys = {};
std::array<char, GLFW_KEY_LAST + 1> Input::previousKeys = {};

void Input::Initialize() {
    currentKeys.fill(GLFW_RELEASE);
    previousKeys.fill(GLFW_RELEASE);
}

void Input::Update()
{
    previousKeys = currentKeys;
    for (int key = 0; key < GLFW_KEY_LAST; key++) {
        currentKeys[key] = glfwGetKey(glfwGetCurrentContext(), key);
    }
}

bool Input::IsKeyPressed(int key) {
    return currentKeys[key] == GLFW_PRESS && previousKeys[key] == GLFW_RELEASE;
}

bool Input::IsKeyDown(int key) {
    return currentKeys[key] == GLFW_PRESS;
}

bool Input::IsKeyReleased(int key) {
    return currentKeys[key] == GLFW_RELEASE && previousKeys[key] == GLFW_PRESS;
}

bool Input::IsKeyUp(int key) {
    return currentKeys[key] == GLFW_RELEASE;
}