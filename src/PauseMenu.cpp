#include "PauseMenu.h"
#include "Window.h"
#include "Assets.h"

PauseMenu* PauseMenu::pauseMenuInstance = nullptr;

PauseMenu::PauseMenu() : Menu()
{
}

PauseMenu::~PauseMenu()
{
	pauseMenuInstance = nullptr;
	buttons.clear();
	texts.clear();
}

PauseMenu* PauseMenu::Instance()
{
	if (pauseMenuInstance == nullptr)
	{
		pauseMenuInstance = new PauseMenu();
		return pauseMenuInstance;
	}

	return pauseMenuInstance;
}

void PauseMenu::InitializeMenu()
{
	vec2 rel_size = vec2(0.4, 0.2);
	float vert_padd = 0.1;
	vec2 rel_pos = vec2((1 - rel_size.x) / 2.f, 0.2);
	vec2 rel_text_size = vec2(0.5, 0.15);

	vec2 rel_text_pos = vec2((1 - rel_size.x - 0.1f) / 2.f, 0.005);

	texts.push_back(UserInterface(rel_text_pos, rel_text_size, Assets::gamePauseText, Assets::spriteShader));

	buttons.push_back(Button(rel_pos, rel_size, Assets::resumeButton, Assets::spriteShader));
	rel_pos.y += rel_size.y + vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::quitButton, Assets::spriteShader));
	//glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);
}

void PauseMenu::UpdateMenu()
{

	// update buttons
	for (Button& btn : buttons) {
		btn.Update();
	}

	// Update texts
	for (UserInterface& text : texts) {
		text.Update();
	}

	if (buttons[0].GetState() == BTN_HOVERED && buttons[0].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = GAME;
	}
	if (buttons[1].GetState() == BTN_HOVERED && buttons[1].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = QUIT_TO_MAIN_MENU_CONF;
	}

	// Releasing the ESCAPE or ENTER key will not register a key press anymore
	if (Input::IsKeyReleased(GLFW_KEY_ESCAPE) && Window::Instance()->keyRegistered || 
		Input::IsKeyReleased(GLFW_KEY_ENTER) && Window::Instance()->keyRegistered)
	{
		Window::Instance()->keyRegistered = false;
	}

	// Pressing the ESCAPE key will resume the game again
	else if (Input::IsKeyPressed(GLFW_KEY_ESCAPE) && !Window::Instance()->keyRegistered)
	{
		Window::Instance()->state = GAME;

		Window::Instance()->keyRegistered = true;
	}
}

void PauseMenu::RenderMenu()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// update projection
	auto projection = ortho(0.0f, (float)Window::Instance()->GetWindowWidth(),
		(float)Window::Instance()->GetWindowHeight(), 0.0f,
		-1.0f, 1.0f);

	glUniform1i(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "spriteImage"), 0);

	glUniformMatrix4fv(glGetUniformLocation(ResourceManager::GetShader(Assets::spriteShader).shaderProgram, "projectionMatrix"),
		1, GL_FALSE, value_ptr(projection));

	for (Button& btn : buttons) {
		btn.Draw(*UserInterface::UiRendererInstance());
	}

	// Render texts
	for (UserInterface& text : texts) {
		text.Draw(*UserInterface::UiRendererInstance());
	}
}

void PauseMenu::DeletePauseMenuInstance()
{
	if (pauseMenuInstance) {
		delete pauseMenuInstance;
		pauseMenuInstance = nullptr;
	}
	else {
		std::cerr << "pauseMenuInstance is not valid to delete\n";
	}
}
