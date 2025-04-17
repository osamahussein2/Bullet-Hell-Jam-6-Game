#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <array>

class Input {
public:

    static void Initialize();
    static void Update();

    static bool IsKeyPressed(int key); // from released to pressed
    static bool IsKeyDown(int key); 
    static bool IsKeyReleased(int key);
    static bool IsKeyUp(int key);

private:
    static std::array<char, GLFW_KEY_LAST + 1> currentKeys;
    static std::array<char, GLFW_KEY_LAST + 1> previousKeys;
};

#endif