#include "Window.h"
#include "Game.h"
#include "MainMenu.h"
#include "QuitConfirmationMenu.h"
#include "Input.h"
#include "Assets.h"

Window* Window::windowInstance = nullptr;
float lastFrame = 0.f;

double Window::mousePosX = 0;
double Window::mousePosY = 0;

int Window::windowWidth = 1200;
int Window::windowHeight = 900;

// Initialize 2 booleans for initializing the reference booleans with the game states
bool falseBool = false;
bool trueBool = true;

Window::Window() : lastPositionX(0.0f), lastPositionY(0.0f), openGLwindow(NULL)
{
}

Window::~Window()
{
  MainMenu::DeleteMainMenuInstance();
  QuitConfirmationMenu::DeleteQuitConfirmationMenuInstance();
  Game::DeleteGameInstance();

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

  glfwSetWindowSizeCallback(openGLwindow, WindowSizeCallback);
  glfwSetKeyCallback(openGLwindow, KeyCallback);
  glfwSetFramebufferSizeCallback(openGLwindow, FrameBufferSizeCallback);
  glfwSetMouseButtonCallback(openGLwindow, MouseButtonCallback);

  Input::Initialize();

  // Initialize game here
  Assets::LoadAssets();
  MainMenu::Instance()->InitializeMenu();
  QuitConfirmationMenu::Instance()->InitializeMenu();
  Game::Instance()->InitializeGame();
}

void Window::UpdateWindow()
{
  float currentFrame = glfwGetTime(); // Get the current time

  // deltaTime is the time between current frame and last frame
  float deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame; // Get the time of the last frame

  glfwPollEvents(); // Waits for any input by the user and processes it in real-time
  Input::Update();

  switch (state){
    case MAIN_MENU:
        {
          //std::cout<<"MAIN_MENU\n";
          MainMenu::Instance()->UpdateMenu();
          MainMenu::Instance()->RenderMenu();
        }
        break;
    case QUIT_CONF:
        {
          //std::cout<<"QUIT_CONF\n";
          QuitConfirmationMenu::Instance()->UpdateMenu();
          QuitConfirmationMenu::Instance()->RenderMenu();
        }
        break;
    case GAME:
        {
          //std::cout<<"GAME\n";
          Game::Instance()->UpdateGame(deltaTime);
          Game::Instance()->HandleInput(deltaTime);
          Game::Instance()->RenderGame(deltaTime);
        }
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
