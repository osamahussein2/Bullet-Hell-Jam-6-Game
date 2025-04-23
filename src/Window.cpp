#include "Window.h"
#include "Game.h"
#include "MainMenu.h"
#include "ResourceManager.h"
#include "Input.h"

Window* Window::windowInstance = nullptr;
float lastFrame = 0.f;

double Window::mousePosX = 0;
double Window::mousePosY = 0;

Window::Window() : lastPositionX(0.0f), lastPositionY(0.0f), openGLwindow(NULL), inMainMenu(true), inGame(false)
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
  glfwSetMouseButtonCallback(openGLwindow, MouseButtonCallback);

  // Initialize game here
  MainMenu::Instance()->InitializeMenu();
}

void Window::UpdateWindow()
{
  float currentFrame = glfwGetTime(); // Get the current time

  // deltaTime is the time between current frame and last frame
  float deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame; // Get the time of the last frame

  glfwPollEvents(); // Waits for any input by the user and processes it in real-time
  Input::Update();

  // Make sure the player is inside the main menu and not the game itself
  if (inMainMenu && !inGame)
  {
      MainMenu::Instance()->UpdateMenu();
      MainMenu::Instance()->RenderMenu();
  }

  // Make sure the player is inside the game and not the main menu
  else if (!inMainMenu && inGame)
  {
      MainMenu::Instance()->~MainMenu();

      Game::Instance()->UpdateGame(deltaTime);
      Game::Instance()->HandleInput(deltaTime);
      Game::Instance()->RenderGame(deltaTime);
  }

  glfwSwapBuffers(openGLwindow); // Removing this will throw an exception error or nothing will pop up
}

void Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
  //if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) // no longer mandatory since the main menu does that
    //glfwSetWindowShouldClose(window, true);
}

void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &mousePosX, &mousePosY);
        //cout << "Cursor Position at (" << mousePosX << " : " << mousePosY << endl;
    }

    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &mousePosX, &mousePosY);
        //cout << "Cursor Position at (" << mousePosX << " : " << mousePosY << endl;
    }
}

float Window::GetMousePositionX()
{
    return mousePosX;
}

float Window::GetMousePositionY()
{
    return mousePosY;
}