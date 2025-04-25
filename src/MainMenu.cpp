#include "MainMenu.h"
#include "QuitConfirmationMenu.h"
#include "Window.h"
#include "Game.h"

MainMenu* MainMenu::mainMenuInstance = nullptr;

mat4 nothingInMain = mat4(0.0f);

MainMenu::MainMenu() : Menu(), projection(nothingInMain), shaderIsCurrentlyUsed(false)
{

}

MainMenu::~MainMenu()
{
	mainMenuInstance = nullptr;

	if (!buttonSpriteRenderers.empty())
	{
		buttonSpriteRenderers.clear();
		buttonSpriteRenderers = vector<SpriteRenderer*>(); // Deallocate the memory of this vector
	}

	if (!buttons.empty())
	{
		buttons.clear();
		buttons = vector<UserInterface*>(); // Deallocate the memory of this vector
	}
}

MainMenu* MainMenu::Instance()
{
	if (mainMenuInstance == nullptr)
	{
		mainMenuInstance = new MainMenu();
		return mainMenuInstance;
	}

	return mainMenuInstance;
}

void MainMenu::InitializeMenu()
{
	shaderIsCurrentlyUsed = false;

	Input::Initialize();

	// Load shaders
	ResourceManager::LoadShader("SpriteRendererVS.glsl", "SpriteRendererFS.glsl", spriteShader);

	// Load textures
	ResourceManager::LoadTexture("Buttons/Play Button.png", playButton);
	ResourceManager::LoadTexture("Buttons/Quit Button.png", quitButton);

	buttonSpriteRenderers.push_back(new SpriteRenderer(ResourceManager::GetShader(spriteShader), true));
	buttonSpriteRenderers.push_back(new SpriteRenderer(ResourceManager::GetShader(spriteShader), true));

	// Play Button
	buttons.push_back(new UserInterface(vec2(Window::Instance()->GetWindowWidth() / 2, 300.0f), vec2(initialButtonSize),
		ResourceManager::GetTexture(playButton), vec3(1.0f)));

	// Quit Button
	buttons.push_back(new UserInterface(vec2(Window::Instance()->GetWindowWidth() / 2, 600.0f), vec2(initialButtonSize),
		ResourceManager::GetTexture(quitButton), vec3(1.0f)));
}

void MainMenu::UpdateMenu()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// If shader isn't in use, tell OpenGL to use the program and set the bool to true for updating the uniform variables
	if (!shaderIsCurrentlyUsed)
	{
		glUseProgram(ResourceManager::GetShader(spriteShader).shaderProgram);

		shaderIsCurrentlyUsed = true;
	}

	// If shader is used, update the projection matrix to match the window's resolution
	else if (shaderIsCurrentlyUsed)
	{
		projection = ortho(0.0f, (float)Window::Instance()->GetWindowWidth(), 
			(float)Window::Instance()->GetWindowHeight(), 0.0f,
			-1.0f, 1.0f);

		glUniform1i(glGetUniformLocation(ResourceManager::GetShader(spriteShader).shaderProgram, "spriteImage"), 0);

		glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(spriteShader).shaderProgram, "projectionMatrix"),
			1, GL_FALSE, value_ptr(projection));
	}

	// Update the buttons positions based on the window resolution
	buttons[0]->position = vec2(Window::Instance()->GetWindowWidth() / 2, Window::Instance()->GetWindowHeight() / 3);
	buttons[1]->position = vec2(Window::Instance()->GetWindowWidth() / 2, Window::Instance()->GetWindowHeight() / 1.5);

	// Update the buttons sizes based on the window resolution
	buttons[0]->size = vec2(
		initialButtonSize.x * (Window::Instance()->GetWindowWidth() / Window::Instance()->GetInitialWindowWidth()),
		initialButtonSize.y * (Window::Instance()->GetWindowHeight() / Window::Instance()->GetInitialWindowHeight()));

	buttons[1]->size = vec2(
		initialButtonSize.x * (Window::Instance()->GetWindowWidth() / Window::Instance()->GetInitialWindowWidth()),
		initialButtonSize.y * (Window::Instance()->GetWindowHeight() / Window::Instance()->GetInitialWindowHeight()));

	// Press the play button with the left mouse button
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && 
		Window::Instance()->GetMousePositionX() >= buttons[0]->position.x && 
		Window::Instance()->GetMousePositionX() <= buttons[0]->position.x + buttons[0]->size.x &&
		Window::Instance()->GetMousePositionY() >= buttons[0]->position.y && 
		Window::Instance()->GetMousePositionY() <= buttons[0]->position.y + buttons[0]->size.y)
	{
		Window::Instance()->state = GAME;
	}

	// Or press play with the right mouse button
	else if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= buttons[0]->position.x &&
		Window::Instance()->GetMousePositionX() <= buttons[0]->position.x + buttons[0]->size.x &&
		Window::Instance()->GetMousePositionY() >= buttons[0]->position.y &&
		Window::Instance()->GetMousePositionY() <= buttons[0]->position.y + buttons[0]->size.y)
	{
		Window::Instance()->state = GAME;
	}

	// Press the quit button with the left mouse button
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= buttons[1]->position.x &&
		Window::Instance()->GetMousePositionX() <= buttons[1]->position.x + buttons[1]->size.x &&
		Window::Instance()->GetMousePositionY() >= buttons[1]->position.y &&
		Window::Instance()->GetMousePositionY() <= buttons[1]->position.y + buttons[1]->size.y)
	{
		Window::Instance()->state = QUIT_CONF;
	}

	// Or press quit with the right mouse button
	else if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= buttons[1]->position.x &&
		Window::Instance()->GetMousePositionX() <= buttons[1]->position.x + buttons[1]->size.x &&
		Window::Instance()->GetMousePositionY() >= buttons[1]->position.y &&
		Window::Instance()->GetMousePositionY() <= buttons[1]->position.y + buttons[1]->size.y)
	{
		Window::Instance()->state = QUIT_CONF;
	}

	// Releasing the ESCAPE key will also take the player to the quit confirmation screen
	if (Input::IsKeyReleased(GLFW_KEY_ESCAPE))
	{
		Window::Instance()->state = QUIT_CONF;
	}
}

void MainMenu::RenderMenu()
{
	// Render the play button
	buttonSpriteRenderers[0]->DrawSprite(ResourceManager::GetTexture(playButton), buttons[0]->position,
		buttons[0]->size, 0.0f, buttons[0]->color);

	// Render the quit button
	buttonSpriteRenderers[1]->DrawSprite(ResourceManager::GetTexture(quitButton), buttons[1]->position,
		buttons[1]->size, 0.0f, buttons[1]->color);
}

void MainMenu::DeleteMainMenuInstance()
{
	if (mainMenuInstance){
		delete mainMenuInstance;
		mainMenuInstance = nullptr;
	}
	else {
		std::cerr<<"mainMenuInstance is not valid to delete\n";
	}
}
