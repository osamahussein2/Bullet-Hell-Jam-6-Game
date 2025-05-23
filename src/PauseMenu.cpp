#include "PauseMenu.h"
#include "Window.h"
#include "Assets.h"
#include "TextRenderer.h"

PauseMenu* PauseMenu::pauseMenuInstance = nullptr;

PauseMenu::PauseMenu() : Menu()
{
}

PauseMenu::~PauseMenu()
{
	pauseMenuInstance = nullptr;
	buttons.clear();
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
	vec2 rel_size = vec2(0.25, 0.15);
	float vert_padd = 0.05;
	vec2 rel_pos = vec2((1 - rel_size.x) / 2.f, 0.3);

	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "resume"));
	rel_pos.y += rel_size.y + vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "options"));
	rel_pos.y += rel_size.y + vert_padd;
	buttons.push_back(Button(rel_pos, rel_size, Assets::buttonTexture, Assets::spriteShader, "main menu"));
	//glUseProgram(ResourceManager::GetShader(Assets::spriteShader).shaderProgram);
}

void PauseMenu::UpdateMenu(float deltaTime)
{

	// update buttons
	for (Button& btn : buttons) {
		btn.Update();
	}

	if (buttons[0].GetState() == BTN_HOVERED && buttons[0].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = GAME;
		ResourceManager::ResumeMusic();
	}
	if (buttons[1].GetState() == BTN_HOVERED && buttons[1].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->prevState = PAUSE_MENU;
		Window::Instance()->state = OPTIONS_MENU;
	}
	if (buttons[2].GetState() == BTN_HOVERED && buttons[2].GetPreviousState() == BTN_PRESSED) {
		Window::Instance()->state = QUIT_TO_MAIN_MENU_CONF;
	}

	if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		Window::Instance()->state = GAME;
		ResourceManager::ResumeMusic();
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

	TextRenderer::Instance()->DrawTextRelCent("paused", vec2(0.5, 0.1), 0.004, vec3(0.8941176470588236, 0, 0.34509803921568627));
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
