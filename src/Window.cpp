#include "Window.h"
#include "Game.h"
#include "ResourceManager.h"

Window* Window::windowInstance = nullptr;
GLFWwindow* Window::openGLwindow = NULL;

Window::Window() : lastPositionX(0.0f), lastPositionY(0.0f)
{
}

Window::~Window()
{
	ResourceManager::Clear();

	// Close all GLFW-related stuff and perhaps terminate the whole program, maybe?
	glfwTerminate();
}

Window* Window::Instance()
{
	if (windowInstance == nullptr)
	{
		windowInstance = new Window();
	}

	return windowInstance;
}

void Window::InitializeWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window to render it to the screen
	openGLwindow = glfwCreateWindow(width, height, title, monitor, share);


	// If our GLFWwindow is NULL, write to the console the window cannot be created and close down GLFW library
	if (openGLwindow == NULL)
	{
		cout << "GLFW Window cannot be created!" << endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(openGLwindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "GLAD cannot be initialized!" << endl;
	}

	glfwSetKeyCallback(openGLwindow, KeyCallback);
	glfwSetFramebufferSizeCallback(openGLwindow, FrameBufferSizeCallback);

	// Initialize game here
	Game::Instance()->InitializeGame();
}

void Window::UpdateWindow()
{
	float deltaTime = 0, lastFrame = 0, currentFrame = 0;

	currentFrame = glfwGetTime(); // Get the current time

	// deltaTime is the time between current frame and last frame
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame; // Get the time of the last frame

	glfwPollEvents(); // Waits for any input by the user and processes it in real-time

	Game::Instance()->UpdateGame(deltaTime);
	Game::Instance()->HandleInput();
	Game::Instance()->RenderGame(deltaTime);

	glfwSwapBuffers(openGLwindow); // Removing this will throw an exception error or nothing will pop up
}

void Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*void Window::MouseCallback(GLFWwindow* window, double positionX, double positionY)
{
}*/