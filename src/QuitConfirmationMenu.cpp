#include "QuitConfirmationMenu.h"
#include "Window.h"
#include "Game.h"
#include "MainMenu.h"

QuitConfirmationMenu* QuitConfirmationMenu::quitConfirmationMenuInstance = nullptr;

mat4 nothingInQuitPrompt = mat4(0.0f);

QuitConfirmationMenu::QuitConfirmationMenu() : Menu(), projection(nothingInQuitPrompt), shaderIsCurrentlyUsed(false)
{

}

QuitConfirmationMenu::~QuitConfirmationMenu()
{
	quitConfirmationMenuInstance = nullptr;

	if (!buttonSpriteRenderers.empty())
	{
		buttonSpriteRenderers.clear();
		buttonSpriteRenderers = vector<SpriteRenderer*>(); // Deallocate the memory of this vector
	}

	if (!buttons.empty())
	{
		buttons.clear();
		buttons = vector<UserInterface*>();
	}

	if (!textSpriteRenderers.empty())
	{
		textSpriteRenderers.clear();
		textSpriteRenderers = vector<SpriteRenderer*>(); // Deallocate the memory of this vector
	}

	if (!texts.empty())
	{
		texts.clear();
		texts = vector<UserInterface*>(); // Deallocate the memory of this vector
	}

}

QuitConfirmationMenu* QuitConfirmationMenu::Instance()
{
	if (quitConfirmationMenuInstance == nullptr)
	{
		quitConfirmationMenuInstance = new QuitConfirmationMenu();
		return quitConfirmationMenuInstance;
	}

	return quitConfirmationMenuInstance;
}

void QuitConfirmationMenu::InitializeMenu()
{
	shaderIsCurrentlyUsed = false;

	Input::Initialize();

	// Load shaders
	ResourceManager::LoadShader("SpriteRendererVS.glsl", "SpriteRendererFS.glsl", spriteShader);

	// Load textures
	ResourceManager::LoadTexture("Buttons/Yes Button.png", yesButton);
	ResourceManager::LoadTexture("Buttons/No Button.png", noButton);
	ResourceManager::LoadTexture("Text Images/Quit Confirmation Text.png", quitConfirmationText);

	buttonSpriteRenderers.push_back(new SpriteRenderer(ResourceManager::GetShader(spriteShader), true));
	buttonSpriteRenderers.push_back(new SpriteRenderer(ResourceManager::GetShader(spriteShader), true));

	textSpriteRenderers.push_back(new SpriteRenderer(ResourceManager::GetShader(spriteShader), true));

	// Yes Button
	buttons.push_back(new UserInterface(vec2(Window::Instance()->GetWindowWidth() / 3, 
		Window::Instance()->GetWindowHeight() / 2), initialButtonSize*Window::Instance()->GetWindowSize(),
		ResourceManager::GetTexture(yesButton), vec3(1.0f)));

	// No Button
	buttons.push_back(new UserInterface(vec2(Window::Instance()->GetWindowWidth() / 1.5, 
		Window::Instance()->GetWindowHeight() / 2), initialButtonSize*Window::Instance()->GetWindowSize(),
		ResourceManager::GetTexture(noButton), vec3(1.0f)));

	// Quit Confirmation Text
	texts.push_back(new UserInterface(vec2(Window::Instance()->GetWindowWidth() / 3,
		Window::Instance()->GetWindowHeight() / 3), initialQuitConfirmationTextSize*Window::Instance()->GetWindowSize(),
		ResourceManager::GetTexture(quitConfirmationText), vec3(1.0f)));
}

void QuitConfirmationMenu::UpdateMenu()
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

	// Update the texts positions based on the window resolution
	texts[0]->position = vec2(Window::Instance()->GetWindowWidth() / 3, Window::Instance()->GetWindowHeight() / 4);

	// Update the texts sizes based on the window resolution
	texts[0]->size = initialQuitConfirmationTextSize * Window::Instance()->GetWindowSize();

	// Update the buttons positions based on the window resolution
	buttons[0]->position = vec2(Window::Instance()->GetWindowWidth() / 3, Window::Instance()->GetWindowHeight() / 2);
	buttons[1]->position = vec2(Window::Instance()->GetWindowWidth() / 1.5, Window::Instance()->GetWindowHeight() / 2);

	// Update the buttons sizes based on the window resolution
	buttons[0]->size = initialButtonSize * Window::Instance()->GetWindowSize();
	buttons[1]->size = initialButtonSize * Window::Instance()->GetWindowSize();

	// Press the yes button with the left mouse button
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= buttons[0]->position.x &&
		Window::Instance()->GetMousePositionX() <= buttons[0]->position.x + buttons[0]->size.x &&
		Window::Instance()->GetMousePositionY() >= buttons[0]->position.y &&
		Window::Instance()->GetMousePositionY() <= buttons[0]->position.y + buttons[0]->size.y)
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
	}

	// Or press yes with the right mouse button
	else if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= buttons[0]->position.x &&
		Window::Instance()->GetMousePositionX() <= buttons[0]->position.x + buttons[0]->size.x &&
		Window::Instance()->GetMousePositionY() >= buttons[0]->position.y &&
		Window::Instance()->GetMousePositionY() <= buttons[0]->position.y + buttons[0]->size.y)
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
	}

	// Press the no button with the left mouse button
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= buttons[1]->position.x &&
		Window::Instance()->GetMousePositionX() <= buttons[1]->position.x + buttons[1]->size.x &&
		Window::Instance()->GetMousePositionY() >= buttons[1]->position.y &&
		Window::Instance()->GetMousePositionY() <= buttons[1]->position.y + buttons[1]->size.y)
	{
		Window::Instance()->state = MAIN_MENU;
	}

	// Or press no with the right mouse button
	else if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS &&
		Window::Instance()->GetMousePositionX() >= buttons[1]->position.x &&
		Window::Instance()->GetMousePositionX() <= buttons[1]->position.x + buttons[1]->size.x &&
		Window::Instance()->GetMousePositionY() >= buttons[1]->position.y &&
		Window::Instance()->GetMousePositionY() <= buttons[1]->position.y + buttons[1]->size.y)
	{
		Window::Instance()->state = MAIN_MENU;
	}

	// Pressing the ESCAPE key will also quit the game
	if (Input::IsKeyDown(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
	}
}

void QuitConfirmationMenu::RenderMenu()
{
	// Render the quit confirmation text
	textSpriteRenderers[0]->DrawSprite(texts[0]->sprite, texts[0]->position,
		texts[0]->size, 0.0f, texts[0]->color);

	// Render the yes button
	buttonSpriteRenderers[0]->DrawSprite(buttons[0]->sprite, buttons[0]->position,
		buttons[0]->size, 0.0f, buttons[0]->color);

	// Render the no button
	buttonSpriteRenderers[1]->DrawSprite(buttons[1]->sprite, buttons[1]->position,
		buttons[1]->size, 0.0f, buttons[1]->color);
}

void QuitConfirmationMenu::DeleteQuitConfirmationMenuInstance()
{
	if (quitConfirmationMenuInstance){
		delete quitConfirmationMenuInstance;
		quitConfirmationMenuInstance = nullptr;
	}
	else {
		std::cerr<<"quitConfirmationMenuInstance is not valid to delete\n";
	}
}
