#include "MainMenu.h"
#include "Window.h"
#include "Game.h"

MainMenu* MainMenu::mainMenuInstance = nullptr;

MainMenu::MainMenu() : Menu(), gameWidth(1200.0f), gameHeight(900.0f)
{

}

MainMenu::~MainMenu()
{
	mainMenuInstance = nullptr;

	buttonSpriteRenderers.clear();
	buttons.clear();
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
	Input::Initialize();

	// Load shaders
	ResourceManager::LoadShader("SpriteRendererVS.glsl", "SpriteRendererFS.glsl", spriteShader);

	// Load textures
	ResourceManager::LoadTexture("Buttons/Play Button.png", playButton);
	ResourceManager::LoadTexture("Buttons/Quit Button.png", quitButton);

	// Configure shaders
	mat4 projection = ortho(0.0f, gameWidth, 0.0f, gameHeight, -1.0f, 1.0f);

	glUseProgram(ResourceManager::GetShader(spriteShader).shaderProgram);

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(spriteShader).shaderProgram, "projectionMatrix"),
		1, GL_FALSE, value_ptr(projection));

	buttonSpriteRenderers.push_back(new SpriteRenderer(ResourceManager::GetShader(spriteShader)));
	buttonSpriteRenderers.push_back(new SpriteRenderer(ResourceManager::GetShader(spriteShader)));

	// Play Button
	buttons.push_back(new UserInterface(vec2(gameWidth / 2, 600.0f), vec2(100.0f, 50.0f),
		ResourceManager::GetTexture(playButton), vec3(1.0f)));

	// Quit Button
	buttons.push_back(new UserInterface(vec2(gameWidth / 2, 300.0f), vec2(100.0f, 50.0f),
		ResourceManager::GetTexture(quitButton), vec3(1.0f)));
}

void MainMenu::UpdateMenu()
{
	// Press the play button with the left mouse button
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && 
		Window::Instance()->GetMousePositionX() >= buttons[0]->position.x && 
		Window::Instance()->GetMousePositionX() <= buttons[0]->position.x + buttons[0]->size.x &&
		Window::Instance()->GetMousePositionY() >= 250.0f && Window::Instance()->GetMousePositionY() <= 300.0f)
	{
		Window::Instance()->inMainMenu = false;
		Window::Instance()->inGame = true;

		Game::Instance()->InitializeGame();
	}

	// Or press play with the right mouse button
	else if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= buttons[0]->position.x &&
		Window::Instance()->GetMousePositionX() <= buttons[0]->position.x + buttons[0]->size.x &&
		Window::Instance()->GetMousePositionY() >= 250.0f && Window::Instance()->GetMousePositionY() <= 300.0f)
	{
		Window::Instance()->inMainMenu = false;
		Window::Instance()->inGame = true;

		Game::Instance()->InitializeGame();
	}

	// Press the quit button with the left mouse button
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= buttons[1]->position.x &&
		Window::Instance()->GetMousePositionX() <= buttons[1]->position.x + buttons[1]->size.x &&
		Window::Instance()->GetMousePositionY() >= 550.0f && Window::Instance()->GetMousePositionY() <= 600.0f)
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
	}

	// Or press quit with the right mouse button
	else if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= buttons[1]->position.x &&
		Window::Instance()->GetMousePositionX() <= buttons[1]->position.x + buttons[1]->size.x &&
		Window::Instance()->GetMousePositionY() >= 550.0f && Window::Instance()->GetMousePositionY() <= 600.0f)
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
	}

	// Pressing the ESCAPE key will also quit the game
	if (Input::IsKeyDown(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
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