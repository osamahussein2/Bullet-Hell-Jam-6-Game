#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <glm.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

enum AppState {
	MAIN_MENU,
	QUIT_CONF,
	GAME,
	PAUSE_MENU,
	QUIT_TO_MAIN_MENU_CONF,
	OPTIONS_MENU,
	CREDITS_MENU,
	GAME_OVER
};

class Window
{
public:
	~Window();

	static Window* Instance();
	static void DeleteWindowInstance();

	// Initialize OpenGL window here
	bool InitializeWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);

	void UpdateWindow();

	float GetMousePositionX();
	float GetMousePositionY();
	glm::vec2 GetMousePosition() { return glm::vec2(GetMousePositionX(), GetMousePositionY()); }

	float GetWindowWidth();
	float GetWindowHeight();

	float GetInitialWindowWidth();
	float GetInitialWindowHeight();

	glm::vec2 GetWindowSize() { return glm::vec2(GetWindowWidth(), GetWindowHeight()); }
	static glm::vec2 GetGameSize() { return glm::vec2(GameWidth, GameHeight); }

	AppState state = MAIN_MENU;

	static int GameWidth;
	static int GameHeight;

	void ToggleFullscreen();
private:
	// Initialize the window's variables to be NULL first before we do anything with it
	Window();

	// Make this function static to use it inside the glfwSetFramebufferSizeCallback function

	/* If I don't make this static, it'll give an error that it cannot convert this function for the Window class
	to a parameter type of GLFWframebuffersizefun */
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	// Get the mouse position
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mode);

	static void WindowSizeCallback(GLFWwindow* window, int width, int height);

	float lastPositionX, lastPositionY;

	static Window* windowInstance;
	
	GLFWwindow* openGLwindow;

	static double mousePosX, mousePosY;
	static int windowWidth, windowHeight;

	const float initialWindowWidth = 1200.0f;
	const float initialWindowHeight = 900.0f;
};

typedef Window WindowInfo;

#endif