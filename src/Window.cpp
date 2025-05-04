#include "Window.h"
#include "Game.h"
#include "MainMenu.h"
#include "QuitConfirmationMenu.h"
#include "PauseMenu.h"
#include "Input.h"
#include "Assets.h"
#include "OptionsMenu.h"
#include "CreditsMenu.h"
#include "GameOverMenu.h"

Window* Window::windowInstance = nullptr;
float lastFrame = 0.f;

double Window::mousePosX = 0;
double Window::mousePosY = 0;

int Window::windowWidth = 0;
int Window::windowHeight = 0;

int Window::GameWidth = 160*4;
int Window::GameHeight = 90*4;

Window::Window() : lastPositionX(0.0f), lastPositionY(0.0f), openGLwindow(NULL)
{
}

Window::~Window()
{
  MainMenu::DeleteMainMenuInstance();
  QuitConfirmationMenu::DeleteQuitConfirmationMenuInstance();
  Game::DeleteGameInstance();
  PauseMenu::DeletePauseMenuInstance();
  QuitToMainMenuConfirmationMenu::DeleteQuitToMainMenuConfirmationMenuInstance();
  OptionsMenu::DeleteOptionsMenuInstance();
  CreditsMenu::DeleteCreditsMenuInstance();
  GameOverMenu::DeleteGameOverMenuInstance();

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

bool Window::InitializeWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
  windowWidth = width;
  windowHeight = height;
  glfwInit();
  #ifdef __EMSCRIPTEN__
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
  #else
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #endif


  // Create a GLFW window to render it to the screen
  openGLwindow = glfwCreateWindow(width, height, title, monitor, share);

  // If our GLFWwindow is NULL, write to the console the window cannot be created and close down GLFW library
  if (openGLwindow == NULL)
  {
    cout << "GLFW Window cannot be created!" << endl;
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(openGLwindow);
  #ifdef __EMSCRIPTEN__
  if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)){
    cout << "GLAD_GLES2 cannot be initialized!" << endl;
    return false;
  }
  #else
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    cout << "GLAD cannot be initialized!" << endl;
    return false;
  }
  #endif

  glfwSetWindowSizeCallback(openGLwindow, WindowSizeCallback);
  glfwSetKeyCallback(openGLwindow, KeyCallback);
  glfwSetFramebufferSizeCallback(openGLwindow, FrameBufferSizeCallback);
  glfwSetMouseButtonCallback(openGLwindow, MouseButtonCallback);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Input::Initialize();

  // Initialize game here
  Assets::LoadAssets();
  MainMenu::Instance()->InitializeMenu();
  QuitConfirmationMenu::Instance()->InitializeMenu();
  Game::Instance()->InitializeGame();
  PauseMenu::Instance()->InitializeMenu();
  QuitToMainMenuConfirmationMenu::Instance()->InitializeMenu();
  OptionsMenu::Instance()->InitializeMenu();
  CreditsMenu::Instance()->InitializeMenu();
  GameOverMenu::Instance()->InitializeMenu();

  return true;
}

void Window::UpdateWindow()
{
  float currentFrame = glfwGetTime(); // Get the current time

  // deltaTime is the time between current frame and last frame
  float deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame; // Get the time of the last frame

  glfwPollEvents(); // Waits for any input by the user and processes it in real-time
  glfwGetCursorPos(openGLwindow, &mousePosX, &mousePosY);

  Input::Update();

  if (Input::IsKeyPressed(GLFW_KEY_F11)) {
      ToggleFullscreen();
    }

  switch (state){
    case MAIN_MENU:
        //std::cout<<"MAIN_MENU\n";
        MainMenu::Instance()->UpdateMenu();
        MainMenu::Instance()->RenderMenu();
        break;
    case QUIT_CONF:
        //std::cout<<"QUIT_CONF\n";
        QuitConfirmationMenu::Instance()->UpdateMenu();
        QuitConfirmationMenu::Instance()->RenderMenu();
        break;
    case GAME:
        //std::cout<<"GAME\n";
        Game::Instance()->HandleInput(deltaTime);
        Game::Instance()->UpdateGame(deltaTime);
        Game::Instance()->RenderGame(deltaTime);
        break;
    case PAUSE_MENU:
        //std::cout<<"PAUSE MENU\n";
        PauseMenu::Instance()->UpdateMenu();
        PauseMenu::Instance()->RenderMenu();
        break;
    case QUIT_TO_MAIN_MENU_CONF:
        //std::cout<<"QUIT TO MAIN MENU CONF\n";
        QuitToMainMenuConfirmationMenu::Instance()->UpdateMenu();
        QuitToMainMenuConfirmationMenu::Instance()->RenderMenu();
        break;
    case OPTIONS_MENU:
        //std::cout<<"OPTIONS MENU\n";
        OptionsMenu::Instance()->UpdateMenu();
        OptionsMenu::Instance()->RenderMenu();
        break;
    case CREDITS_MENU:
        //std::cout<<"CREDITS MENU\n";
        CreditsMenu::Instance()->UpdateMenu();
        CreditsMenu::Instance()->RenderMenu();
        break;
    case GAME_OVER:
        //std::cout<<"GAME OVER MENU\n";
        GameOverMenu::Instance()->UpdateMenu();
        GameOverMenu::Instance()->RenderMenu();
        break;
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
}

void Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
}

float Window::GetMousePositionX()
{
    return mousePosX;
}

float Window::GetMousePositionY()
{
    return mousePosY;
}

float Window::GetWindowWidth()
{
    return static_cast<float>(windowWidth);
}

float Window::GetWindowHeight()
{
    return static_cast<float>(windowHeight);
}

float Window::GetInitialWindowWidth()
{
    return initialWindowWidth;
}

float Window::GetInitialWindowHeight()
{
    return initialWindowHeight;
}

void Window::DeleteWindowInstance()
{
    if (windowInstance){
        delete windowInstance;
        windowInstance = nullptr;
    }
    else {
        std::cerr<<"windowInstance is not valid to delete\n";
    }
}
void Window::ToggleFullscreen() {
  static bool isFullscreen = false;
  static int savedX, savedY, savedWidth, savedHeight;

  if (!isFullscreen) {
      // Save current position and size
      glfwGetWindowPos(openGLwindow, &savedX, &savedY);
      glfwGetWindowSize(openGLwindow, &savedWidth, &savedHeight);

      // Get the primary monitor's resolution
      GLFWmonitor* monitor = glfwGetPrimaryMonitor();
      const GLFWvidmode* mode = glfwGetVideoMode(monitor);

      glfwSetWindowMonitor(
        openGLwindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate
      );
  } else {
      // Restore windowed mode
      glfwSetWindowMonitor(
        openGLwindow, nullptr, savedX, savedY, savedWidth, savedHeight, GLFW_DONT_CARE
      );
  }

  isFullscreen = !isFullscreen;
}